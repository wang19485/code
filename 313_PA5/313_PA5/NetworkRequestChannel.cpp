#include "NetworkRequestChannel.h"
#include "common.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <thread>
using namespace std;

/*--------------------------------------------------------------------------*/
/* CONSTRUCTOR/DESTRUCTOR FOR CLASS   R e q u e s t C h a n n e l  */
/*--------------------------------------------------------------------------*/

NetworkRequestChannel::NetworkRequestChannel(const string server_name, const string port)
{
    struct addrinfo hints, *res;
    // first, load up address structs with getaddrinfo():
    
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    int status;
    //getaddrinfo("www.example.com", "3490", &hints, &res);
    if ((status = getaddrinfo(server_name.c_str(), port.c_str(), &hints, &res)) != 0) {
        cerr << "getaddrinfo: " << gai_strerror(status) << endl;
        exit(0);
    }
    // make a socket:
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sockfd < 0)
    {
        perror ("Cannot create scoket");
        exit(0);
    }
    
    // connect!
    if (connect(sockfd, res->ai_addr, res->ai_addrlen)<0)
    {
        perror ("Cannot Connect");
        exit(0);
    }
    //cout << "Successfully connected" << endl;
}

NetworkRequestChannel::NetworkRequestChannel(const string port, void (*handle_process_loop)(NetworkRequestChannel*)){ // server
    struct addrinfo hints, *serv;
    struct sockaddr_storage their_addr; // connector's address information
    socklen_t sin_size;
    char s[INET6_ADDRSTRLEN];
    int rv;
    
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP
    //cout << AI_PASSIVE << endl;
    if ((rv = getaddrinfo(NULL, port.c_str(), &hints, &serv)) != 0) {
        cerr  << "getaddrinfo: " << gai_strerror(rv) << endl;
        exit(0);
    }
    if ((sockfd = socket(serv->ai_family, serv->ai_socktype, serv->ai_protocol)) == -1) {
        perror("server: socket");
        exit(0);
    }
    if (::bind(sockfd, serv->ai_addr, serv->ai_addrlen) == -1) {
        
        close(sockfd);
        perror("server: bind");
        exit(0);
    }
    freeaddrinfo(serv); // all done with this structure
    
    if (listen(sockfd, 20) == -1) {
        perror("listen");
        exit(1);
    }
    
    cout << "server: waiting for connections..." << endl;
    char buf [1024];
    while(1)
    {  // main accept() loop
        sin_size = sizeof their_addr;
        int slave_socket = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (slave_socket == -1) {
            perror("accept");
            continue;
        }
        NetworkRequestChannel *sc = new NetworkRequestChannel(slave_socket);
        thread client_thread(handle_process_loop, sc);
        client_thread.detach();
    }
}

NetworkRequestChannel::NetworkRequestChannel(int fd){
    sockfd = fd;
}

NetworkRequestChannel::~NetworkRequestChannel()
{
    close(sockfd);
}

char* NetworkRequestChannel::cread(int *len)
{
    char * buf = new char [MAX_MESSAGE];
    int length;
    length = recv(sockfd, buf, MAX_MESSAGE, 0);
    if (len)    // the caller wants to know the length
        *len = length;
    return buf;
}

int NetworkRequestChannel::cwrite(char* msg, int len)
{
    //mtx.lock();
    if (len > MAX_MESSAGE){
        EXITONERROR("cwrite");
    }
    if (send(sockfd, msg, len, 0) < 0){
        EXITONERROR("cwrite");
    }
    //mtx.unlock();
    return len;
}

