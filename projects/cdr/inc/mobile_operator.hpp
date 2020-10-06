#ifndef __MOBILE_OPERATOR_HPP__
#define __MOBILE_OPERATOR_HPP__

#include <cstddef>
#include <iostream>
#include <string>
#include "record.hpp"
#include "cdr.hpp"

namespace experis{

class MobileOperator : public Record{

    typedef size_t VoiceInNum;
    typedef size_t VoiceOutNum;
    typedef size_t SmsOutNum;
    typedef size_t SmsInNum;
    typedef std::string OpName;

public:
    MobileOperator(Cdr* a_cdr);
    ~MobileOperator(){}
    //MobileOperator(const MobileOperator &a_other)=deafault;
    //MobileOperator& operator=(const MobileOperator &a_other)=deafault;

    const VoiceInNum& GetVoiceInNum()const{return m_voiceInNum;}
    const VoiceOutNum& GetVoiceOutNum()const{return m_voiceOutNum;}
    const SmsInNum& GetSmsInNum()const{return m_smsInNum;}
    const SmsOutNum& GetSmsOutNum()const{return m_smsOutNum;}
    const OpName& GetOpName()const{return m_opName;}

    bool operator==(const MobileOperator& a_other);
    MobileOperator& operator+=(const MobileOperator& a_other);
    MobileOperator& operator()(const MobileOperator& a_other);
  
private:
    OpName m_opName;
    VoiceInNum m_voiceInNum;
    VoiceOutNum m_voiceOutNum;
    SmsInNum m_smsInNum;
    SmsOutNum m_smsOutNum;

};


} // namespace experis

#endif //__MOBILE_OPERATOR_HPP__


    /* MobileOperator(OpName a_name ,VoiceInNum a_voiceInNum, VoiceOutNum a_voiceOutNum,SmsInNum a_smsInNum, SmsOutNum a_smsOutNum)
    : m_opName(a_name)
    , m_voiceInNum(a_voiceInNum)
    , m_voiceOutNum(a_voiceOutNum)
    , m_smsInNum(a_smsInNum)
    , m_smsOutNum(a_smsOutNum) {
    } */

    /* 
    void SetVoiceInNum(VoiceInNum a_voiceInNewNum){m_voiceInNum=a_voiceInNewNum;}
    void SetVoiceOutNum(VoiceOutNum a_voiceOutNewNum){m_voiceOutNum=a_voiceOutNewNum;}
    void SetSmsInNum(SmsInNum a_smsInNewNum){m_smsInNum=a_smsInNewNum;}
    void SetSmsOutNum(SmsOutNum a_smsOutNewNum){m_smsOutNum=a_smsOutNewNum;}
     */
