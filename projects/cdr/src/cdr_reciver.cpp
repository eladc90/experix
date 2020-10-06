#include "cdr_reciver.hpp"
#include "cdr.hpp"

namespace experis {

std::string CdrReciver::replyMsg = "Ready for next msg";


CdrReciver::CdrReciver(CdrSafeContainer& a_queue, IChannel& a_channel)
: m_container(a_queue)
, m_protocol(a_channel) {
}

CdrReciver::~CdrReciver() {
}

void CdrReciver::Run() {
    while(1) {
        try {
            std::string recivedString;
            m_protocol.Receive(recivedString);
            Cdr* cdrPtr = new Cdr(recivedString);
            m_container.Enqueue(cdrPtr);
            m_protocol.Send(replyMsg);
        }
        catch(const std::exception& a_exception) {
            break;
        }
    }
}

} //experis