#ifndef __PROTOCOL_HPP__
#define __PROTOCOL_HPP__

#include <string>
#include "i_channel.hpp"

namespace experis {

class Protocol {
public:
    Protocol(IChannel& a_channel) throw();
    ~Protocol() throw();

    void Send(const std::string& a_string);
    void Receive(std::string& a_string);

private:
    Protocol(const Protocol& a_other); //copy not allowed
    Protocol& operator=(const Protocol& a_other); //assignment not allowed

    static const size_t g_maxBufferSize = 512;

    IChannel& m_channel;
};

} //experis

#endif //__PROTOCOL_HPP__