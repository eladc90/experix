#ifndef __CDR_RECIVER_HPP__
#define __CDR_RECIVER_HPP__

//#include <string>

#include "runnable.hpp"
#include "cyc_waitable_queue.hpp"
#include "protocol.hpp"

namespace experis {

class Cdr;

class CdrReciver : public Runnable {
    typedef WaitableQueue<Cdr*> CdrSafeContainer;
public:
    CdrReciver(CdrSafeContainer& a_queue, IChannel& a_channel);
    ~CdrReciver();

    void Run();

private:
    static std::string replyMsg;

    CdrSafeContainer& m_container;
    Protocol m_protocol;
};

} //experis

#endif //__CDR_RECIVER_HPP__