#include "../include/connection.h"
#include <iostream>
#include <thread>




int main()
{
	Connection conn(8080 , "127.0.0.1");

	std::thread thread(&Connection::run , &conn);
	thread.join();
	return 0;
}
