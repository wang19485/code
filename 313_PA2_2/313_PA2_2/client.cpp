/*
 Tanzir Ahmed
 Department of Computer Science & Engineering
 Texas A&M University
 Date  : 2/8/19
 */
#include "common.h"
#include "FIFOreqchannel.h"

using namespace std;


int main(int argc, char *argv[]){
    int pid = fork();
    if (pid == 0) {
        char *arglist[] = {"./dataserver",NULL};
        execvp(arglist[0], arglist);
    }else{
        int n = 100;    // default number of requests per "patient"
        int p = 15;        // number of patients
        srand(time_t(NULL));
        
        FIFORequestChannel chan ("control", FIFORequestChannel::CLIENT_SIDE);
        // sending a non-sense message, you need to change this
        int c;
        int patient = 0;
        double time = 0.0;
        int ecg = 0;
        string filename_in = "";
        bool channel = 0;
        while ((c = getopt(argc, argv, "p:t:e:f:c::")) != -1) {
            switch (c) {
                case 'p':
                    patient = atoi(optarg);
                    break;
                case 't':
                    time = atof(optarg);
                    break;
                case 'e':
                    ecg = atoi(optarg);
                    break;
                case 'f':
                    filename_in = optarg;
                    break;
                case 'c':
                    channel = 1;
                    break;
                default:
                    cout <<"ERROR: Unacceptable command line argument, see report to get the correct format" << endl;
                    exit(-5);
                    break;
            }
        }
        if (filename_in == "" && channel == 0) {
            if (ecg != 0) {
                datamsg *d = new datamsg(patient, time, ecg);
                char *buff = new char[sizeof(datamsg)];
                buff = (char*)d;
                chan.cwrite (buff, sizeof(datamsg));
                char *r = chan.cread();
                double *o = (double*)r;
                cout << *o << endl;
            }else{
                struct timeval start,end;
                gettimeofday(&start, NULL);
                ios_base::sync_with_stdio(false);
                
                string filename1 = "received/x";
                filename1 += to_string(patient);
                filename1 += ".csv";
                ofstream output;
                output.open(filename1);
                double i = 0;
                
                while (i <= 59.996) {
                    output << i << ",";
                    
                    datamsg *d1 = new datamsg(patient,i,1);
                    datamsg *d2 = new datamsg(patient,i,2);
                    
                    char *buff1 = new char[sizeof(datamsg)];
                    buff1 = (char*)d1;
                    chan.cwrite(buff1, sizeof(datamsg));
                    char *r1 = chan.cread();
                    double *o1 = (double*)r1;
                    output << *o1 << ",";
                    
                    char *buff2 = new char[sizeof(datamsg)];
                    buff2 = (char*)d2;
                    chan.cwrite(buff2, sizeof(datamsg));
                    char *r2 = chan.cread();
                    double *o2 = (double*)r2;
                    output << *o2 << endl;
                    
                    i+=0.004;
                }
                output.close();
                
                gettimeofday(&end, NULL);
                double time_taken;
                time_taken = ((end.tv_sec - start.tv_sec) * 1e6 + (end.tv_usec - start.tv_usec)) * 1e-6;
                cout << "Transfer all points finished" << endl;
                cout << "Time taken: " << fixed << time_taken << setprecision(6) << "sec" << endl;
                // Requsting Data Points finished
            }
        }else if (filename_in != ""){
            filemsg *f = new filemsg(0,0);
            char *buff_file = new char[sizeof(filemsg)+sizeof(filename_in)];
            buff_file = (char*)f;
            for (int i = 0; i < filename_in.size(); i++) {
                *(buff_file+sizeof(filemsg)+i) = filename_in[i];
            }
            *(buff_file+sizeof(filemsg)+filename_in.size()) = '\0';
            chan.cwrite(buff_file, sizeof(filemsg)+sizeof(filename_in));
            char *rr = chan.cread();
            __int64_t *file_length = (__int64_t*)rr;
            cout << "Length: " << *file_length << endl;
            
            struct timeval start2,end2;
            gettimeofday(&start2, NULL);
            ios_base::sync_with_stdio(false);
            
            ofstream o_file;
            o_file.open("received/y1.csv");
            __int64_t offset = 0;
            int size = MAX_MESSAGE;
            while (offset < *file_length) {
                filemsg *f1 = new filemsg(offset,size);
                char *buff_file1 = new char[sizeof(filemsg)+sizeof(filename_in)];
                buff_file1 = (char*)f1;
                for (int i = 0; i < filename_in.size(); i++) {
                    *(buff_file1+sizeof(filemsg)+i) = filename_in[i];
                }
                *(buff_file1+sizeof(filemsg)+sizeof(filename_in)) = '\0';
                chan.cwrite(buff_file1, sizeof(filemsg)+sizeof(filename_in));
                char *rr1 = chan.cread();
                o_file << rr1;
                offset += size;
                if (*file_length - offset < MAX_MESSAGE) {
                    size = *file_length - offset;
                }
            }
            o_file.close();
            gettimeofday(&end2, NULL);
            double time_taken2;
            time_taken2 = ((end2.tv_sec - start2.tv_sec) * 1e6 + (end2.tv_usec - start2.tv_usec)) * 1e-6;
            cout << "Transfer file finished" << endl;
            cout << "Time taken: " << fixed << time_taken2 << setprecision(6) << "sec" << endl;
        }else if (channel != 0){
            channelmsg *ch = new channelmsg();
            char *buffer_ch = new char[sizeof(channelmsg)];
            buffer_ch = (char*)ch;
            chan.cwrite (buffer_ch, sizeof(channelmsg));
            FIFORequestChannel chan2 ("data1_",FIFORequestChannel::CLIENT_SIDE);
            
            cout << "Test new channel:" << endl;
            datamsg *new_d = new datamsg(10, 59.00, 2);
            char *new_buff = new char[sizeof(datamsg)];
            new_buff = (char*)new_d;
            chan2.cwrite (new_buff, sizeof(datamsg));
            char *new_r = chan2.cread();
            double *new_o = (double*)new_r;
            cout << *new_o << endl;
            
            //closing the new channel
            MESSAGE_TYPE m = QUIT_MSG;
            chan2.cwrite (&m, sizeof (MESSAGE_TYPE));
            wait(NULL);
        }
        // closing the channel
        MESSAGE_TYPE m = QUIT_MSG;
        chan.cwrite (&m, sizeof (MESSAGE_TYPE));
        
        
    }
    
}
