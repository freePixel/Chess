#include "../include/connection.h"



Connection::Connection(int SRC_PORT , const char* SRC_IP)
{
    sock_id = 0;
    int opt = 1;
    for(int i=0;i<sizeof(clients)/sizeof(int);i++)
    	clients[i] = 0;

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

    addrlen = sizeof(address);
}

void Connection::sendMessage(Client& client , const char* message)
{
	
}

void Connection::getMessages()
{
    
}

void Connection::run()
{

    std::cout << "Server is active, waiting for clients \n";
    int max_sd , sd , activity , new_socket;
    char buffer[512];
    while(true)
    {
        FD_ZERO(&readfds);

        FD_SET(sock_id , &readfds);
        max_sd = sock_id;

        for(int i=0;i<MAX_CLIENTS;i++)
        {
            sd = clients[i];
            if(sd > 0)
                FD_SET(sd , &readfds);

            if(sd > max_sd)
                max_sd = sd;
        }

        activity = select(max_sd + 1 , &readfds , NULL , NULL , NULL);

        if((activity < 0) && (errno != EINTR))
        {
            throw std::runtime_error("Select error");
        }

        if(FD_ISSET(sock_id , &readfds))
        {
            new_socket = accept(sock_id , (struct sockaddr*)&address , (socklen_t*)&addrlen);
            if(new_socket < 0)
                throw std::runtime_error("Accept error");

        

            std::cout << "new connection " << "\n";

            const char* hello = "{'message' : 'hello client!'}";
            send(new_socket , hello , strlen(hello) , 0);


            for(int i=0;i<MAX_CLIENTS;i++)
            {
                if(clients[i] == 0)
                {
                    clients[i] = new_socket;
                    break;
                }
            }

        }

        for(int i=0;i<MAX_CLIENTS;i++)
        {
            sd = clients[i];
            if(FD_ISSET(sd , &readfds))
            {
                int valread = read(sd , buffer , 512);
                if(valread == 0)
                {
                    getpeername(sd , (struct sockaddr*)&address , (socklen_t*)&addrlen);

                    std::cout << "client disconnected \n";
                    
                    close(sd);
                    clients[i] = 0;
                }
                else{
                    buffer[valread] = '\0';
                    
                }
            }
        }



    }
}