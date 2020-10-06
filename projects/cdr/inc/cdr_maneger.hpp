#ifndef _CDR_MANEGER_HPP_
#define _CDR_MANEGER_HPP_
#include "tcp_producer.hpp"

namespace experis {

class CdrManeger {
public:
    CdrManeger() : m_channel(1952) {}
    ~CdrManeger() {}
    void Run();
private:

    CdrManeger(const CdrManeger& a_other);
    CdrManeger& operator=(const CdrManeger& a_other);

    TcpProducer m_channel;

};
}
#endif // _CDR_MANEGER_HPP_