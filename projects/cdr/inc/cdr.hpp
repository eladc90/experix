#ifndef __Cdr_HPP__
#define __Cdr_HPP__
#include <string>
#include <stdlib.h>

namespace experis {

/* typedef struct IMSI
{
    short MCC;          // country code
    short MNC;          // network operator
    std::string MSIN;   // phone number
}IMSI;
 */
/* typedef struct IMEI
{

}IMEI; */


//struct Msg{
//    int m_fileSN; // sequnce number
//    size_t m_IMSI; // MCC, MNC, MSIN
//    std::string m_IMEI; // device id
//    std::string m_msgTpye;
//    size_t m_MSISDN; // phone number of the client
//    std::string m_callDate;
//    std::string m_callTime;
//    unsigned int m_Duration; // in seconds
//    size_t m_bytesRcv;
//    size_t m_bytesSend;
//    std::string m_secParty; // in call will be the MSISDN of the calle(other side)  
//};


class Cdr {
private:
    enum MSG_FIELDS {
        FILE_SQ_NUM = 0,
        IMSI,// MCC, MNC, MSIN
        DEVICE_ID,
        MSG_TYPE,
        MSISDN, // phone number of the client
        CALL_DATE,
        CALL_TIME,
        CALL_DURATION,
        BYTES_RCV,
        BYTES_SEND,
        SECOND_PARTY, // in call will be the MSISDN of the calle(other side)  
        MCC, //country
        MNS, // operator
        MSIN // phone number
    };
    

public:

    enum USEGES {
        MOC = 0,
        MTC,
        SMS_MO,
        SMS_MT,
        D,
        U,
        B,
        X
    };
    
    typedef std::string* Msg;

    Cdr(std::string a_msg);
    ~Cdr(){}

    std::string GetImsi()        { return m_cdr[IMSI]; }
    std::string GetMCC()        { return m_cdr[MCC]; }
    std::string GetMNS()        { return m_cdr[MNS]; }
    std::string GetMSIN()        { return m_cdr[MSIN]; }
    std::string GetDeviceId()    { return m_cdr[DEVICE_ID]; }
    std::string GetMsisdn()      { return m_cdr[MSISDN]; }
    std::string GetCallDate()    { return m_cdr[CALL_DATE]; }
    std::string GetSecondParty() { return m_cdr[SECOND_PARTY]; }
    
    USEGES GetMsgType();
    
    size_t GetFileSqNum()   {return atoi( m_cdr[FILE_SQ_NUM].c_str()); }
    size_t GetCallTime()    {return atoi( m_cdr[CALL_TIME].c_str()); }  
    size_t GetCallDuration(){return atoi( m_cdr[CALL_DURATION].c_str()); }
    size_t GetBytesRcv()    {return atoi( m_cdr[BYTES_RCV].c_str()); }
    size_t GetBytesSnd()    {return atoi( m_cdr[BYTES_SEND].c_str()); }

private:
    Cdr& operator=(const Cdr& a_other);
    Cdr(const Cdr& a_other);

    Msg m_cdr;
};

}//namespace wasc

#endif //__Cdr_HPP__