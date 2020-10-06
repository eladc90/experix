#include <unistd.h>
#include <iostream>
#include <errno.h>
#include <assert.h>
#include <sys/socket.h> // socket 
#include <list>
#include <cstring>  
#include <sys/types.h> 
#include <sys/socket.h>
#include "tcp_producer.hpp"

static const unsigned int BACK_LOG = 100; 
static const unsigned int MAX_DESC = 1024;
static const unsigned int SIZE_OF_MSG = 256; 

namespace experis {

TcpProducer::TcpProducer(unsigned int a_port) 
: m_port(a_port)
, m_sockList()  {
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

    if (setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, &optVal, sizeof(optVal)) < 0) {
        assert(!"no documented error for setsockopt");
    }
    int status = bind(m_socket, reinterpret_cast<struct sockaddr *>(&m_serverSin) ,sizeof(struct sockaddr_in));
    if (status < 0) {
        if(errno == EADDRINUSE) {
            throw AddInUse();
        }
        else {
            assert(!"no documented error for bind");
        }
    }
    if((listen(m_socket, BACK_LOG)) < 0) {
            switch(errno) {
                case EADDRINUSE:
                    throw AddInUse();
                    break;
                default:
                    assert(!"no documented error for listen");
                    break;
            }
    }

    FD_ZERO(&m_master);
    FD_SET(m_socket, &m_master); 
}

void TcpProducer::Receive(char *a_buffer, size_t a_bufferSize) {
    socklen_t sizeOfServ = sizeof(m_serverSin);

    if(!a_buffer) {
        throw NullError();
    }
    
    m_masterCopy = m_master;

    int activity;
    do {
        activity = select(MAX_DESC, &m_masterCopy, NULL, NULL, NULL);
        if (activity < 0) {
            switch(errno) {
                case EINTR:
                    throw RecivedSignal();
                    break;

                case ENOMEM:
                    throw NoMemory();
                    break;

                default:
                    assert(!"no documented error for select");
                    break;

            }
        }
    } while(!activity);

    if(FD_ISSET(m_socket, &m_masterCopy))
    {
        socklen_t sizeOfServ = sizeof(m_serverSin);
        int sock = accept(m_socket, reinterpret_cast<struct sockaddr *>(&m_serverSin), &sizeOfServ);
        if (sock < 0) {
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

        else
        {
            FD_SET(sock , &m_master);
            m_sockList.push_back(sock);
        } 
        --activity;
    }

    if(activity > 0)
    {
        ReceiveMsg(a_buffer, a_bufferSize ,activity);
    }
}

void TcpProducer::ReceiveMsg(char *a_buffer , size_t a_bufferSize ,int a_numOfAct) {
    std::list<unsigned int>::iterator sockItr = m_sockList.begin();
    while(a_numOfAct) {

        if(FD_ISSET(*sockItr, &m_master)) {
            
            if(0 >= recv(*sockItr, a_buffer, a_bufferSize - 1, 0)) {
                FD_CLR(*sockItr, &m_master);
                close(*sockItr);
                m_sockList.erase(sockItr);
            }
            else {
                m_currentFD = *sockItr;
                break;
            }
            --a_numOfAct;
            ++sockItr;
        }
    }
}

void TcpProducer::Send(const char * a_buffer, size_t a_bufferSize) {    
    if(send(m_currentFD, a_buffer, strlen(a_buffer), 0) < 0) {
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