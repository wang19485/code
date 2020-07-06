#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <fcntl.h>
using namespace std;

int client (char * server_name)
{
    string host = "";
    string request = "";
    string input_url = string(server_name);
    string url = input_url;
    size_t found_http = input_url.find("https://");
    if (found_http != string::npos) {
        url = input_url.substr(found_http+8);
    }
    size_t found = url.find("/");
    if(found != string::npos){
        host = url.substr(0,found);
        request = url.substr(found+1);
    }
    else{
        host = url;
    }
    
	struct addrinfo hints, *res;
	int sockfd;

	// first, load up address structs with getaddrinfo():

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	int status;
	if ((status = getaddrinfo(host.c_str(), "80", &hints, &res))!= 0) {
        cerr << "getaddrinfo: " << gai_strerror(status) << endl;
        return -1;
    }

	// make a socket:
	sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (sockfd < 0)
	{
		perror ("Cannot create scoket");	
		return -1;
	}

	// connect!
	if (connect(sockfd, res->ai_addr, res->ai_addrlen)<0)
	{
		perror ("Cannot Connect");
		return -1;
	}
    
    string bufSend = "GET /" + request + " HTTP/1.1\r\nHost: " + host + "\r\nConnection: close\r\n\r\n";
    cout << "Send successfully" << endl << bufSend << endl;
    if (send (sockfd, bufSend.c_str(), bufSend.size(), 0) <= 0){
        perror("client: Send failure");
    }
    
    int fd = open("receive.html", O_WRONLY|O_TRUNC|O_CREAT, 0666);
    bool count = false;
    while (true){
        char buf [1024];
        size_t size = recv (sockfd, buf, sizeof (buf), 0);
        if (size <= 0){
            break;
        }else{
            if (count == false) {
                count = true;
                string remove = string(buf);
                size_t found_header= remove.find("\r\n\r\n");
                if (found_header != string::npos) {
                    string after_remove = remove.substr(found_header+4);
                    write(fd, after_remove.c_str(), size-found_header-4);
                }
            }else{
                write(fd, buf, size);
            }
        }
    }
    close(sockfd);
    close(fd);
	return 0;
}


int main (int ac, char** av)
{
	if (ac < 2){
        cout << "Enter url please" << endl;
        exit (-1);
    }
	client (av [1]);
}
