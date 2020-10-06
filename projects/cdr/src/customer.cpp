#include <assert.h>
#include "customer.hpp"
#include "cdr.hpp"

namespace experis {

Customer::Customer(Cdr* a_cdr) {

    m_msisdn = a_cdr->GetMsisdn();
    m_bytesIn = a_cdr->GetBytesRcv();
    m_bytesOut = a_cdr->GetBytesSnd();
    

    switch (a_cdr->GetMsgType()){ 

    case Cdr::MOC:
        m_voiceOut = a_cdr->GetCallDuration();
        break;
    
    case Cdr::MTC:
        m_voiceIn = a_cdr->GetCallDuration();
        break;

    case Cdr::SMS_MO:
        m_smsOut = 1;
        break;

    case Cdr::SMS_MT:
        m_smsIn = 1;
        break;

    default:
        assert(!"invalid cdr msg type");    
        break; 
    }
}

/* 
Customer& Customer::operator+=(Cdr* a_cdr){

    switch(a_cdr->GetMsgType()) {
            case Cdr::MOC:
            m_voiceOut += a_cdr->GetCallDuration();
            break;

            case Cdr::MTC:
               m_voiceIn += a_cdr->GetCallDuration();
            break;

            case Cdr::SMS_MO:
                m_smsOut += 1;
            break;

            case Cdr::SMS_MT:
                m_smsIn += 1;
            break;

            case Cdr::D:
                m_bytesIn += a_cdr->GetBytesRcv();
            break;

            // not relevent for customer {
            case Cdr::U:
            case Cdr::B:
            case Cdr::X: break;
            // }
            default: assert(!"cdr not valid");
            break;
    }
}
 */

Customer& Customer::operator+=(const Customer& a_other){

    m_voiceOut += a_other.m_voiceOut;
    m_voiceIn +=  a_other.m_voiceIn;
    m_smsOut +=  a_other.m_smsOut;
    m_smsIn += a_other.m_smsOut;
    m_bytesIn+= a_other.m_bytesIn;

    return *this;
}


Customer& Customer::operator()(const Customer& a_other){

    return this->operator+=(a_other);

}

bool  Customer::operator==(const Customer& a_other){
     return m_msisdn == a_other.m_msisdn;

}


} //experis
