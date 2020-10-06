#include <string>
#include "cdr_sender.hpp"
#include "cyc_waitable_queue.hpp"

namespace experis {

CdrSender::CdrSender(lineQueue* a_Wqueue, IChannel& a_channel)
: m_waitQueue(a_Wqueue)
, m_stringProtocol(a_channel)
{

}

void CdrSender::Run() {
    std::string lineToSend;
    std::string getLine;
    while(true) {
        m_waitQueue->Dequeue(&lineToSend);
        m_stringProtocol.Send(lineToSend);
        m_stringProtocol.Receive(getLine);
    }
}

}// experis