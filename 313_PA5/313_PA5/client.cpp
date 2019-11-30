#include "common.h"
#include "BoundedBuffer.h"
#include "Histogram.h"
#include "common.h"
#include "HistogramCollection.h"
#include <string>
#include <fcntl.h>
#include "NetworkRequestChannel.h"

using namespace std;

class patient_thread{
public:
    int i; // patient number
    int n; // request
    BoundedBuffer *request_buffer;
    int size;
    string filename = "";
    __int64_t *file_length;
    
    patient_thread(int _i, int _n, BoundedBuffer *buffer):i(_i),n(_n),request_buffer(buffer){}
    patient_thread(int _size, string filename, __int64_t *file_length, BoundedBuffer *buffer):size(_size),filename(filename),file_length(file_length),request_buffer(buffer){}
};

class worker_thread{
public:
    NetworkRequestChannel *worker_channel;
    BoundedBuffer *request_buffer_worker;
    Histogram *hist;
    string filename = "";
    int fd;
    const char* filename_in_char;
    string quit = "";
    
    worker_thread(NetworkRequestChannel *worker_channel, BoundedBuffer *request_buffer_worker, Histogram *hist):
    worker_channel(worker_channel), request_buffer_worker(request_buffer_worker), hist(hist){}
};

void * patient_function(void *arg)
{
    /* What will the patient threads do? */
    patient_thread *data_arg = (patient_thread*)arg;
    if (data_arg->filename == "") {
        double time = 0.0;
        for (int i = 0; i < data_arg->n; i++) {
            datamsg *d = new datamsg(data_arg->i, time, 1);
            char *buff = new char[sizeof(datamsg)];
            buff = (char*)d;
            vector<char> data(buff, buff+sizeof(datamsg));
            data_arg->request_buffer->push(data);
            time += 0.004;
        }
    }else{
        int offset = 0;
        while (offset < *data_arg->file_length) {
            filemsg *f1 = new filemsg(offset,data_arg->size);
            char *buff_file1 = new char[sizeof(filemsg)+sizeof(data_arg->filename)+1];
            buff_file1 = (char*)f1;
            for (int i = 0; i < data_arg->filename.size(); i++) {
                *(buff_file1+sizeof(filemsg)+i) = data_arg->filename[i];
            }
            *(buff_file1+sizeof(filemsg)+data_arg->filename.size()) = '\0';
            vector<char> data(buff_file1,buff_file1+sizeof(filemsg)+sizeof(data_arg->filename)+1);
            data_arg->request_buffer->push(data);
            offset += data_arg->size;
            if (*data_arg->file_length - offset < data_arg->size) {
                data_arg->size = *data_arg->file_length - offset;
            }
           
        }
    }
}

void *worker_function(void *arg)
{
        while (true) {
            worker_thread *worker_arg = (worker_thread*)arg;
            vector<char> request = worker_arg->request_buffer_worker->pop();
            char *request_char = (char*)request.data();
            if (*(MESSAGE_TYPE*)request_char == QUIT_MSG) {
                worker_arg->worker_channel->cwrite(request_char, sizeof(QUIT_MSG));
                //cout << "quit"<< endl;
                break;
            }else if (*(MESSAGE_TYPE*)request_char == DATA_MSG){
                worker_arg->worker_channel->cwrite(request_char, sizeof(datamsg));
                char *response = worker_arg->worker_channel->cread();
                double *ret = (double*) response;
                worker_arg->hist->update(*ret);
            }else if (*(MESSAGE_TYPE*)request_char == FILE_MSG){
                filemsg *request_f = (filemsg*)request_char;
                worker_arg->worker_channel->cwrite(request_char, sizeof(filemsg)+sizeof(worker_arg->filename)+1);
                char *response = worker_arg->worker_channel->cread();
                int fd = open (worker_arg->filename_in_char,O_RDWR);
                lseek(fd, request_f->offset, SEEK_SET);
                write(fd, response, request_f->length);
                close(fd);
            }
        }
}

int main(int argc, char *argv[])
{
    int n = 100;    //default number of requests per "patient"
    int p = 10;     // number of patients [1,15]
    int w = 100;    //default number of worker threads
    int b = 20; 	// default capacity of the request buffer, you should change this default
	int m = MAX_MESSAGE; 	// default capacity of the file buffer
    srand(time_t(NULL));
    
    
    /*int pid = fork();
    if (pid == 0){
		// modify this to pass along m
        execl ("dataserver", "dataserver", (char *)NULL);
        
    }*/
    int c = 0;
    string filename_in = "";
    string host_name = "";
    string port="";
    while ((c = getopt(argc, argv, "n:w:b:p:f:h:r:")) != -1) {
        switch (c) {
            case 'n':
                n = atoi(optarg);
                break;
            case 'p':
                p = atoi(optarg);
                break;
            case 'w':
                w = atoi(optarg);
                break;
            case 'b':
                b = atoi(optarg);
                break;
            case 'f':
                filename_in = optarg;
                break;
            case 'h':
                host_name = optarg;
                break;
            case 'r':
                port = optarg;
                break;
            default:
                cout <<"ERROR: Unacceptable command line argument" << endl;
                exit(-2);
                break;
        }
    }
    
    NetworkRequestChannel *chan = new NetworkRequestChannel(host_name, port);
    BoundedBuffer request_buffer(b);
	HistogramCollection hc;
    
    struct timeval start, end;
    gettimeofday (&start, 0);
    
    /* Start all threads here */
    if (filename_in == "") {
        for (int j = 0; j < p; j++) {
            Histogram *hist = new Histogram(10, -2, 2);
            vector<thread> threads;
            patient_thread *patient_array;
            //for (int i = 0; i < p; i++) {
                patient_array = new patient_thread(j+1, n, &request_buffer);
                threads.push_back(thread(patient_function, (void*)patient_array));
            //}
            vector<thread> threads2;
            worker_thread *worker_array[w];
            for (int i = 0; i < w; i++) {

                NetworkRequestChannel *new_channel = new NetworkRequestChannel(host_name, port);
                
                worker_array[i] = new worker_thread(new_channel, &request_buffer, hist);
                threads2.push_back(thread(worker_function, (void*)worker_array[i]));
            }
            /* Join all threads here */
            for (int i = 0; i < threads.size(); i++) {
                threads[i].join();
            }
            for (int i = 0; i < w; i++) {
                MESSAGE_TYPE q = QUIT_MSG;
                vector<char>data((char*) &q,(char*) &q + sizeof(QUIT_MSG));
                request_buffer.push(data);
            }
            for (int i = 0; i < threads2.size(); i++) {
                threads2[i].join();
            }
            for (int i = 0; i < w; i++) {
                delete worker_array[i]->worker_channel;
                //delete worker_array[i];
            }
            hc.add(hist);
            
        }
        hc.print ();
    }else{
        filemsg *f = new filemsg(0,0);
        char *buff_file = new char[sizeof(filemsg)+sizeof(filename_in)+1];
        buff_file = (char*)f;
        for (int i = 0; i < filename_in.size(); i++) {
            *(buff_file+sizeof(filemsg)+i) = filename_in[i];
        }
        *(buff_file+sizeof(filemsg)+filename_in.size()) = '\0';
        chan->cwrite(buff_file, sizeof(filemsg)+sizeof(filename_in)+1);
        char *rr = chan->cread();
        __int64_t *file_length = (__int64_t*)rr;
        cout << "Length: " << *file_length << endl;
        
        struct timeval start2,end2;
        gettimeofday(&start2, NULL);
        ios_base::sync_with_stdio(false);
        
        string name1 = "received/";
        string name = name1 + filename_in;
        const char *filename_in_char = name.c_str();
        
        int fd = open (filename_in_char,O_RDWR|O_TRUNC|O_CREAT,0666);
        close(fd);
        __int64_t offset = 0;
        
        int size = 0;
        if (*file_length >= MAX_MESSAGE) {
            size = MAX_MESSAGE;
        }else{
            size = *file_length;
        }
        patient_thread *patient = new patient_thread(size,filename_in,file_length,&request_buffer);
        thread thread_obj(patient_function,(void*)patient);
        
        vector<thread> threads2;
        worker_thread *worker_array[w];
        for (int i = 0; i < w; i++) {
            
            NetworkRequestChannel *new_channel = new NetworkRequestChannel(host_name, port);
            
            worker_array[i] = new worker_thread(new_channel, &request_buffer, NULL);
            worker_array[i]->filename = filename_in;
            worker_array[i]->fd = fd;
            worker_array[i]->filename_in_char = filename_in_char;
            
            threads2.push_back(thread(worker_function, (void*)worker_array[i]));
        }
        
        thread_obj.join();
        for (int i = 0; i < w; i++) {
            /*MESSAGE_TYPE q = QUIT_MSG;
            vector<char>data ((char*) &q,(char*) &q + sizeof(QUIT_MSG));
            //cout << data.size() << endl;
            request_buffer.push(data);
            cout << "Iam" << i << endl;*/
            MESSAGE_TYPE m = QUIT_MSG;
            char *data = (char *)&m;
            vector<char> v(data,data+sizeof(MESSAGE_TYPE));
            request_buffer.push(v);
        }
        for (int i = 0; i < w; i++) {
            threads2[i].join();
        }
        
        for (int i = 0; i < w; i++) {
            //delete worker_array[i]->worker_channel;
            //delete worker_array[i];
        }
        
        gettimeofday(&end2, NULL);
    }

    gettimeofday (&end, 0);
    int secs = (end.tv_sec * 1e6 + end.tv_usec - start.tv_sec * 1e6 - start.tv_usec)/(int) 1e6;
    int usecs = (int)(end.tv_sec * 1e6 + end.tv_usec - start.tv_sec * 1e6 - start.tv_usec)%((int) 1e6);
    cout << "Took " << secs << " seconds and " << usecs << " micor seconds" << endl;
    
    
    MESSAGE_TYPE q = QUIT_MSG;
    chan->cwrite ((char *) &q, sizeof (MESSAGE_TYPE));
    cout << "All Done!!!" << endl;
    delete chan;
}
