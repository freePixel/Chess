#include "../include/connection.h"

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <functional>
#include <stdexcept>
#include <iostream>

Connection::Connection(int SV_PORT , const char* SV_IP)
{
    sock_id = 0;
    struct sockaddr_in serv_addr;
    
    sock_id = socket(AF_INET , SOCK_STREAM , 0);

    if(sock_id < 0)
    {
        throw std::runtime_error("Socket creation failed \n");
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port   = htons(SV_PORT);

    if(inet_pton(AF_INET , SV_IP , &serv_addr.sin_addr) <= 0)
    {
        throw std::runtime_error("Invalid IP address \n");
    }

    if(connect(sock_id , (struct sockaddr*)&serv_addr , sizeof(serv_addr)) < 0)
    {
        throw std::runtime_error("Connection failed \n");
    }
    

}


void Connection::sendMessage(message m)
{
    //get size
    int size = m.get_size();

    unsigned char bytes[4];
    bytes[0] = (size >> 24) && 0xFF;
    bytes[1] = (size >> 16) && 0xFF;
    bytes[2] = (size >> 8) && 0xFF;
    bytes[3] = size && 0xFF;

    std::string send_data = bytes[0] + bytes[1] + bytes[2] + bytes[3] + m.data;
    send(sock_id , send_data.c_str() , size + 4 , 0);
}

void Connection::getMessages()
{
    

}

void Connection::run()
{
    std::cout << "client is running " << "\n";
    char buffer[512];
    while(true)
    {
        int size = recv(sock_id , buffer , sizeof(buffer) , 0);
        if(size == 0)
        {
            std::cout << "Server disconnected (?) \n";
            return;
        }
        else{
            std::cout << buffer << "\n";
        }
    }
    
}