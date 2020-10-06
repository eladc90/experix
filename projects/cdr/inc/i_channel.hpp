#ifndef _ICHANNEL_HPP_
#define _ICHANNEL_HPP_
#include <cstddef>

namespace experis {

class IChannel {
public:
    IChannel();
    virtual ~IChannel();
    virtual void Send(const char * a_buffer, size_t a_bufferSize) = 0;
    virtual void Receive(char * a_buffer, size_t a_bufferSize) = 0;

private:
    IChannel(const IChannel& a_other);
    IChannel& operator=(const IChannel& a_other);
};

}//experis

#endif //  _ICHANNEL_HPP_