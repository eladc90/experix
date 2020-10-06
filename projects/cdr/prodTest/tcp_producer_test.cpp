#include <iostream>
#include "tcp_producer.hpp"

int main () {
    
    char buffer[512];
    experis::TcpProducer prod(8080);
    int i = 0;
    while (true) {
        prod.Receive(buffer, 511);
        std::cout << "message#" << i  << ": " << buffer << std::endl << std::endl;
        prod.Send(buffer, 511);
        ++i;
    }   
    return 0;
}