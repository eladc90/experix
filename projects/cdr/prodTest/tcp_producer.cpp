#include <iostream>
#include <errno.h>
#include <sys/socket.h> // socket 
#include <list>
#include <cstring>  
#include <sys/types.h> 
#include <assert.h>
#include <sys/socket.h>
#include "tcp_exception.hpp"
#include "tcp_producer.hpp"

static const unsigned int BACK_LOG = 100; 
static const unsigned int MAX_DESC = 1024;
static const unsigned int SIZE_OF_MSG = 256; 

namespace experis {

TcpProducer::TcpProducer(unsigned int a_port) 
: m_port(a_port)
{
    socklen_t sizeOfServ = sizeof(m_serverSin);
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
    InitializeServer(&m_serverSin, m_port, sizeOfServ);
}

void TcpProducer::InitializeServer(struct sockaddr_in* a_server, unsigned int a_portNum, int a_size)
{
    int optVal = 1;
	memset(a_server, 0, a_size);
	a_server->sin_family = AF_INET; 
	a_server->sin_addr.s_addr = INADDR_ANY;
	a_server->sin_port = htons(a_portNum);
    socklen_t len = sizeof(m_serverSin);

    if (setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, &optVal, sizeof(optVal)) < 0)
    {
        throw "setsockopt socket opt failed";// TODO
    }
    int status = bind(m_socket, reinterpret_cast<struct sockaddr *>(&m_serverSin) ,sizeof(struct sockaddr_in));
    if (status < 0)
    {
        throw "bind socket opt failed";// TODO 
    }
    if((listen(m_socket, BACK_LOG)) < 0)
    {
                
            switch(errno) {

                case EADDRINUSE:
                    throw AddInUse();
                    break;

                default:
                    assert(!"no documented error for listen");
                    break;

            }
    }
    int sock = 0;
    socklen_t sizeOfServ = sizeof(m_serverSin);
    m_reciveFd = accept(m_socket, reinterpret_cast<struct sockaddr *>(&m_serverSin), &sizeOfServ);
    std::cout << m_reciveFd << "this is the socket connect" << std::endl;
    if (m_reciveFd < 0)
    {
        switch(errno) {
        case ECONNABORTED:
            throw ConnectionAborted();
            break;

        case EINTR:
            throw RecivedSignal();
            break;

        case EMFILE:
        case ENFILE:
            throw LimitReached();
            break;

        case ENOBUFS:
        case ENOMEM:
            throw NoMemory();
            break;

        default:
            assert(!"no documented error for accept");
            break;
        } 
    }
}

void TcpProducer::Receive(char *a_buffer, size_t a_bufferSize) {
    int status = 0;
    if(0 >= (status = recv(m_reciveFd, a_buffer, a_bufferSize - 1, 0))) {
        std::cout << status << std::endl;
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


void TcpProducer::Send(const char * a_buffer, size_t a_bufferSize) {    
    if(send(m_reciveFd, a_buffer, strlen(a_buffer), 0) < 0)
    {
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

}//experis