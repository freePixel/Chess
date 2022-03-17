#pragma once

#define MAX_CLIENTS 30

#include <vector>

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
        std::vector<const message>& getMessages();
    private:

    int clients[MAX_CLIENTS];
    

        
};