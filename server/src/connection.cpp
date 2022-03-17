#include "../include/connection.h"

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <functional>
#include <stdexcept>
#include <iostream>

Connection::Connection(int SRC_PORT , const char* SRC_IP)
{
    int sock_id = 0;

    for(int i=0;i<sizeof(clients)/sizeof(int);i++)
    	client[i] = 0;

    sock_id = socket(AF_INET , SOCK_STREAM , 0);
    if(sock_id == 0)
    {
    	throw std::runtime_error("Socket creation failed \n");
		
    }	

    int OPT = 1;
    if(setsockopt(sock_id , SOL_SOCKET , SO_REUSEADDR , (char*)&opt , sizeof(opt)) < 0)
    {
	throw std::runtime_error("setsockopt failed");
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(SRC_PORT);

    if(bind(sock_id , (struct sockaddr*)&address,sizeof(address))<0)
    {
	throw std::runtime_error("bind() failed");
    }
    

    if(listen(sock_id , MAX_CLIENTS) < 0)
    {
	throw std::runtime_error("Listen error");
    }

    int addrlen = sizeof(address);
}

void Connection::sendMessage(Client& client , const char* message)
{
	
}

std::vector<const message>& Connection::getMessages()
{
    
}

