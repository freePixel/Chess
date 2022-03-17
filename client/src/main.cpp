#include "../include/connection.h"
#include <iostream>
int main()
{
	Connection conn(8080 , "127.0.0.1");
	
	conn.sendMessage({"Hello"});

	conn.getMessages();

	return 0;
}
