#ifndef __PARSER_HPP__
#define __PARSER_HPP__
#include <string>

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


class Parser {
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
        SECOND_PARTY // in call will be the MSISDN of the calle(other side)  
    };
    
public:
    typedef std::string* Msg;

    Parser();
    ~Parser(){}
  //  Parser(const Parser& a_other);
  //  Parser& operator=(const Parser& a_other);

    //Api Functions

    Msg BuildMsg(std::string& a_msg);

private:
};

}//namespace wasc

#endif //__PARSER_HPP__