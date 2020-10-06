#ifndef _TCP_CONSUMER_HPP_
#define _TCP_CONSUMER_HPP_

#include <netinet/in.h> //struct sockaddr_in
#include <string>

#include "i_channel.hpp"

namespace experis {
class TCPConsumer : public IChannel {
public:
    TCPConsumer(unsigned int a_port, const std::string& a_ip);
    virtual ~TCPConsumer();

    virtual void Send(const char * a_buffer, size_t a_bufferSize);
    virtual void Receive(char * a_buffer, size_t a_bufferSize);

private:
    TCPConsumer(const TCPConsumer& a_other);
    TCPConsumer& operator=(const TCPConsumer& a_other);

    void initSin();
    void initSocket();

    unsigned int m_port;
    std::string m_ip;
    struct ::sockaddr_in m_sin;
    int m_socket;
};

}//experis

#endif // _TCP_CONSUMER_HPP_