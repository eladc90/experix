#ifndef __CUSTOMER_HPP__
#define __CUSTOMER_HPP__

#include <string>
#include "record.hpp"
#include "cdr.hpp"

namespace experis{

class Customer : public Record {

    typedef std::string MSISDN;
    typedef size_t VoiceIn;
    typedef size_t VoiceOut;
    typedef double BytesIn;
    typedef double BytesOut;
    typedef size_t SmsIn;
    typedef size_t SmsOut;

public:
    Customer(Cdr* a_cdr);
    //~Customer(); deaf
    //Customer(const Customer& a_other); deaf
    //Customer& operator=(const Customer& a_other); deaf

    //API Functions
    
    Customer& operator+=(const Customer& a_other);
    Customer& operator()(const Customer& a_other);
    bool operator==(const Customer& a_other);

    const MSISDN& GetMSISDN()const { return m_msisdn;}
    const VoiceIn& GetVoiceIn()const { return m_voiceIn;}
    const VoiceOut& GetVoiceOut()const { return m_voiceOut;}
    const BytesIn& GetBytesIn()const { return m_bytesIn;}
    const BytesOut& GetBytesOut()const { return m_bytesOut;}
    const SmsIn& GetSmsIn()const { return m_smsIn;}
    const SmsOut& GetSmsOut()const { return m_smsOut;}


private:
    
    MSISDN m_msisdn;
    VoiceIn m_voiceIn;
    VoiceOut m_voiceOut;
    BytesIn m_bytesIn;
    BytesOut m_bytesOut;
    SmsIn m_smsIn;
    SmsOut m_smsOut;

};

} //experis

#endif //__CUSTOMER_HPP__
    /*  


    void SetMSISDN(const MSISDN& a_other){ m_msisdn += a_other;}
    void SetVoiceIn(const VoiceIn& a_other){ m_voiceIn += a_other;}
    void SetVoiceOut(const VoiceOut& a_other){ m_voiceOut += a_other;}
    void SetBytesIn(const BytesIn& a_other){ m_bytesIn += a_other;}
    void SetBytesOut(const BytesOut& a_other){ m_bytesOut += a_other;}
    void SetSmsIn(const SmsIn& a_other){ m_smsIn += a_other;}
    void SetSmsOut(const SmsOut& a_other){ m_smsOut += a_other;} */