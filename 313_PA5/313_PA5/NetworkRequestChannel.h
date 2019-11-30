#ifndef NetworkRequestChannel_h
#define NetworkRequestChannel_h

#include <stdio.h>

#include "common.h"
#include <mutex>

class NetworkRequestChannel
{
private:
    int sockfd;
    mutex mtx;
public:
    NetworkRequestChannel(const string host_name, const string port);
    NetworkRequestChannel(const string port, void (*handle_process_loop)(NetworkRequestChannel*));
    NetworkRequestChannel(int fd);
    
    ~NetworkRequestChannel();
    
    char* cread(int *len=NULL);
    /* Blocking read of data from the channel. Returns a string of characters
     read from the channel. Returns NULL if read failed. */
    
    int cwrite(char *msg, int msglen);
    /* Write the data to the channel. The function returns the number of characters written
     to the channel. */
};

#endif /* NetworkRequestChannel_h */
