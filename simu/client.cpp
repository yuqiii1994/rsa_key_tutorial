// referenced http://beej.us/guide/bgnet/html/multi/index.html

/*
** client.c -- a stream socket client demo
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <iostream>
#include "../algo/utils.hpp"

#define MAXDATASIZE 100 // max number of bytes we can get at once 

using namespace std;

void sigchld_handler(int s){
    // waitpid() might overwrite errno, so we save and restore it:
    int saved_errno = errno;

    while(waitpid(-1, NULL, WNOHANG) > 0);

    errno = saved_errno;
}

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char *argv[])
{
    int sockfd, numbytes = 0;  
    char buf[MAXDATASIZE];
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];
    struct sigaction sa;

    cout << "input the host ip (try 'ifconfig' on terminal to find your local server ip): " << endl;
    string ip_addr;
    cin >> ip_addr;
    char* str_ip = (char*)malloc(ip_addr.length());
    strcpy(str_ip, ip_addr.c_str());
    cout << "choose a port number [2001 - 65536]: " << endl;
    char port_num[5];
    cin >> port_num;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo(str_ip, port_num, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and connect to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("client: socket");
            continue;
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("client: connect");
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "client: failed to connect\n");
        return 2;
    }

    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
            s, sizeof s);
    printf("client: connecting to %s\n", s);

    // signal action function will be activated by the fork() that spwans child processes
    sa.sa_handler = sigchld_handler; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    // SIGCHLD passes child process info to sa struct, the info includes running time, etc.
    // sigaction returns 0 for successfully recieving child signals to run the handler func
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }
    cout << "type a message to send" << endl;
    string sendt_msg;
    cin >> sendt_msg;
    numbytes = sendt_msg.length();
    if (send(sockfd, &numbytes, 1, 0) == -1){
        perror("send");
        exit(0);
    }
    if (send(sockfd, sendt_msg.c_str(), sendt_msg.length(), 0) == -1){
        perror("send");
        exit(0);
    }

    freeaddrinfo(servinfo); // all done with this structure

    close(sockfd);

    return 0;
}