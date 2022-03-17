#pragma once

#include <vector>

struct message
{
	const char* data;

	int get_size()
	{
		int size = 0;
		const char * p = data;
		while(*p != '\0') size++;
		return size;
	}
};

class Connection
{
	public:
		
		Connection(int DST_PORT , const char* DST_IP);
		void sendMessage(message m);
		
		void getMessages();
	private:
		void listen();
		int sock_id;
		char buffer[512];
		

};
