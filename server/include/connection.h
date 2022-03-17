#pragma once

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

        
};