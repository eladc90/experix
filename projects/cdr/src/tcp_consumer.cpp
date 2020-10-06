#include <sys/types.h> //socket
#include <sys/socket.h> //socket
#include <arpa/inet.h> //inet_addr
#include <unistd.h>
#include <cerrno> //errno
#include <cstring>
#include <cassert>
#include <iostream>

#include "tcp_consumer.hpp"
#include "tcp_exception.hpp"

namespace experis {

TCPConsumer::TCPConsumer(unsigned int a_port, const std::string& a_ip)
: m_port(a_port)
, m_ip(a_ip) {
    initSin();
    initSocket();

    if(connect(m_socket, (struct sockaddr*)&m_sin, sizeof(m_sin)) < 0) {
        close(m_socket);

        switch (errno) {
            case ECONNREFUSED :
                throw ConnectionRefused();
            case EINTR :
                throw RecivedSignal();
            case ENETUNREACH :
                throw UnreachableNetwork();
            case EPROTOTYPE:
                throw ProtocolErr();
            case ETIMEDOUT:
                throw Timeout();
            default:
                assert(!"Not documented connection error");
        }
    }
}

TCPConsumer::~TCPConsumer() {
    close(m_socket);
}

void TCPConsumer::Send(const char * a_buffer, size_t a_bufferSize) {
    std::cout <<"send!!!!!!!!!!!!!!!" << std::endl;
    if(!a_buffer) {
        throw NullError();
    }

    if(send(m_socket, a_buffer, a_bufferSize, 0) < 0) {
        switch(errno) {
            case EAGAIN:
                throw Block();
            case ECONNRESET:
                throw ConnectionReset();
            case EINTR:
                throw RecivedSignal();
            case ENOMEM:
                throw NoMemory();
            case EPIPE:
                throw ShutDown();
            default:
                 assert(!"Not documented send error");
        }
    }
}

void TCPConsumer::Receive(char * a_buffer, size_t a_bufferSize) {
    if(!a_buffer) {
        throw NullError();
    }

    if(recv(m_socket, a_buffer, a_bufferSize, 0) < 0) {
        switch(errno) {
            case EAGAIN:
                throw Block();
            case EINTR:
                throw RecivedSignal();
            case ENOMEM:
                throw NoMemory();
            default:
                assert(!"Not documented recieve error");
        }
    }
}

void TCPConsumer::initSin() {
    memset(&m_sin, 0, sizeof(m_sin));
	m_sin.sin_family = AF_INET; 
	m_sin.sin_addr.s_addr = inet_addr(m_ip.c_str());
	m_sin.sin_port = htons(m_port);
}

void TCPConsumer::initSocket() {
    m_socket = socket(AF_INET, SOCK_STREAM, 0);

    if(m_socket < 0) {
        switch(errno) {
            case EINVAL : 
                throw NotAvaliable();
            case EMFILE :
                throw LimitReached();
            case ENOBUFS :
            case ENOMEM :
                throw InsufficientMemory();
            default :
                assert(!"Not documented socket error");
        }
    }
}

} //experis