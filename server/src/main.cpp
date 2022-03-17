#include "../include/connection.h"
#include <thread>


int main(int argc , char* argv[])
{
    Connection conn(8080 , "127.0.0.1");

    std::thread thread(&Connection::run , &conn);

    std::cout << "hello world" << "\n";

    thread.join();
    
}