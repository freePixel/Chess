#include "../include/connection.h"

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdexcept>

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
