#ifndef _CDR_SENDER_HPP
#define _CDR_SENDER_HPP
#include "cyc_waitable_queue.hpp"
#include "protocol.hpp"
#include "runnable.hpp"

namespace experis {

class CdrSender : public Runnable {
public:
typedef WaitableQueue<std::string> lineQueue;

    CdrSender(lineQueue* a_Wqueue, IChannel& a_channel);
    ~CdrSender() {}

    virtual void Run();

private:
    CdrSender(const CdrSender& a_other);
    CdrSender& operator=(const CdrSender& a_other);

    lineQueue* m_waitQueue;
    Protocol m_stringProtocol;
};

}//experis


#endif // !_CDR_SENDER_HPP