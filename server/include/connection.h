#pragma once

#define MAX_CLIENTS 30

#include <vector>
#include <stdio.h> 
#include <string.h>   //strlen 
#include <stdlib.h> 
#include <errno.h> 
#include <unistd.h>   //close 
#include <arpa/inet.h>    //close 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros 
#include <stdexcept>
#include <iostream>

struct Client
{

};

struct message
{
    const char* data;
};

class Connection
{
    public:
        Connection(int SRC_PORT , const char* SRC_IP);
        void sendMessage(Client& client , const char* message);
        void  getMessages();
        void run();
    private:

    int clients[MAX_CLIENTS];
    
    fd_set readfds;  
    int addrlen;
    int sock_id = 0;
    struct sockaddr_in address;
        
};