#ifndef _TCP_CHANNEL_HPP_
#define _TCP_CHANNEL_HPP_
#include <string>
#include <cstddef>
#include <list>
#include <netinet/in.h> // sockaddr_in
#include "tcp_exception.hpp"
#include "i_channel.hpp"

namespace experis {

class TcpProducer : public IChannel {
    typedef std::list<unsigned int> socketList;

public:
    TcpProducer(unsigned int a_port);
    ~TcpProducer() {}

    virtual void Receive(char * a_buffer, size_t a_bufferSize);
    virtual void Send(const char * a_buffer, size_t a_bufferSize);

private:
    TcpProducer(const TcpProducer& a_other);
    TcpProducer& operator=(const TcpProducer& a_other);

    void InitializeServer(struct sockaddr_in* _server, unsigned int _portNum, int _size);
    void ReceiveMsg(char *a_buffer , size_t a_bufferSize ,int a_numOfAct);

    unsigned int m_port;
    unsigned int m_socket;
    fd_set m_masterCopy;
    fd_set m_master;
    struct sockaddr_in m_serverSin;
    socketList m_sockList;
    unsigned int m_currentFD;
};

}//experis

#endif // _TCP_CHANNEL_HPP_