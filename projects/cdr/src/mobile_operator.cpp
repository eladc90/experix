#include "mobile_operator.hpp"
#include <assert.h>


namespace experis{

MobileOperator::MobileOperator(Cdr* a_cdr){

    m_opName = a_cdr->GetMNS();

    switch (a_cdr->GetMsgType())
    {
    case Cdr::MOC:
        m_voiceOutNum = a_cdr->GetCallDuration();
        break;
    
    case Cdr::MTC:
        m_voiceInNum = a_cdr->GetCallDuration();
        break;
    case Cdr::SMS_MO:
        m_smsOutNum = 1;
         break;

    case Cdr::SMS_MT:
        m_smsInNum = 1;
        break;
    default:
        assert(!"invalid cdr msg type");    
        break; 
    }
}


MobileOperator& MobileOperator::operator+=(const MobileOperator& a_other){

    m_voiceOutNum += a_other.m_voiceOutNum;
    m_voiceInNum +=  a_other.m_voiceInNum;
    m_smsOutNum +=  a_other.m_smsOutNum;
    m_smsInNum += a_other.m_smsOutNum;

    return *this;
}


MobileOperator& MobileOperator::operator()( const MobileOperator& a_other){

    return this->operator+=(a_other);

}

bool MobileOperator::operator==(const MobileOperator& a_other){
    
    return (a_other.m_opName==m_opName);
        
}



}//namespace experis



/* MobileOperator& MobileOperator::operator+=(Cdr* a_cdr){

    switch(a_cdr->GetMsgType()) {

            case Cdr::MOC:
            m_voiceOutNum += a_cdr->GetCallDuration();
                break;

            case Cdr::MTC:
              m_voiceInNum += a_cdr->GetCallDuration();
                break;

            case Cdr::SMS_MO:
                m_smsOutNum += 1;
                break;

            case Cdr::SMS_MT:
                m_smsInNum += 1;
                break;

            case Cdr::U:
            case Cdr::B:
            case Cdr::X:
                break;

            default: assert(!"cdr not valid");
                break;
    }

    return *this;
} */
