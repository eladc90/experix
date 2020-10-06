#include "protocol.hpp"

namespace experis {
Protocol::Protocol(IChannel& a_channel) throw()
: m_channel(a_channel) {
}

Protocol::~Protocol() throw() {
}

void Protocol::Receive(std::string& a_string) {
    char buffer[g_maxBufferSize];
    m_channel.Receive(buffer, g_maxBufferSize);
    a_string = buffer;
}

void Protocol::Send(const std::string& a_string) {
    m_channel.Send(a_string.c_str(), a_string.size());
}

} //experis