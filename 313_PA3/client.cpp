#include "common.h"
#include "BoundedBuffer.h"
#include "Histogram.h"
#include "common.h"
#include "HistogramCollection.h"
#include "FIFOreqchannel.h"
using namespace std;


void * patient_function(void *arg)
{
    /* What will the patient threads do? */
    
}

void *worker_function(void *arg)
{
    /*
		Functionality of the worker threads	
    */

    
}
int main(int argc, char *argv[])
{
    int n = 100;    //default number of requests per "patient"
    int p = 10;     // number of patients [1,15]
    int w = 100;    //default number of worker threads
    int b = 20; 	// default capacity of the request buffer, you should change this default
	int m = MAX_MESSAGE; 	// default capacity of the file buffer
    srand(time_t(NULL));
    
    
    int pid = fork();
    if (pid == 0){
		// modify this to pass along m
        execl ("dataserver", "dataserver", (char *)NULL);
        
    }
    
	FIFORequestChannel* chan = new FIFORequestChannel("control", FIFORequestChannel::CLIENT_SIDE);
    BoundedBuffer request_buffer(b);
	HistogramCollection hc;
    
    int c = 0;
    int patient = 0;
    string filename_in = "";
    while ((c = getopt(argc, argv, "n:p:w:b:f:")) != -1) {
        switch (c) {
            case 'n':
                break;
            case 'p':
                patient = atoi(optarg);
                break;
            case 'w':
                ecg = atoi(optarg);
                break;
            case 'b':
                break;
            case 'f':
                filename_in = optarg;
                break;
            default:
                cout <<"ERROR: Unacceptable command line argument, see report to get the correct format" << endl;
                exit(-5);
                break;
        }
    }
	
    struct timeval start, end;
    gettimeofday (&start, 0);

    /* Start all threads here */
	

	/* Join all threads here */
    gettimeofday (&end, 0);
	hc.print ();
    int secs = (end.tv_sec * 1e6 + end.tv_usec - start.tv_sec * 1e6 - start.tv_usec)/(int) 1e6;
    int usecs = (int)(end.tv_sec * 1e6 + end.tv_usec - start.tv_sec * 1e6 - start.tv_usec)%((int) 1e6);
    cout << "Took " << secs << " seconds and " << usecs << " micor seconds" << endl;

    MESSAGE_TYPE q = QUIT_MSG;
    chan->cwrite ((char *) &q, sizeof (MESSAGE_TYPE));
    cout << "All Done!!!" << endl;
    delete chan;
    
}
