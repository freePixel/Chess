#pragma once

#include <vector>

struct message
{
	const char* data;
};

class Connection
{
	public:
		
		Connection(int DST_PORT , const char* DST_IP);
		void run();
		void sendMessage(message m);
		std::vector<const message>& getMessages();
		
	private:
		int sock_id;

		

};
