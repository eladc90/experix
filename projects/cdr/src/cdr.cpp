#include <string>
#include <algorithm>
#include <cstring>
#include <iostream>
#include "cdr.hpp"

namespace experis {

static const int CDR_SIZE = 14;

Cdr::Cdr(std::string a_msg) {
    size_t from = 0;
    size_t to = 0;
    int i = 0;
    m_cdr = new std::string[CDR_SIZE];
    size_t len = strlen(a_msg.c_str());
    while( to < len ) {
        to = a_msg.find_first_of("|", from);
        m_cdr[i] = a_msg.substr(from, to - from);
        from = to + 1;
        ++i;
    }
    m_cdr[i] = m_cdr[IMSI].substr(0, 3);
    ++i;
    m_cdr[i] = m_cdr[IMSI].substr(3, 2);
    ++i;
    m_cdr[i] = m_cdr[IMSI].substr(5, 10);
}

Cdr::USEGES Cdr::GetMsgType() {

    if (0 == m_cdr[MSG_TYPE].compare("MOC")) {
        return MOC;
    }
    if (0 == m_cdr[MSG_TYPE].compare("MTC")) {
        return MTC;
    }
    if (0 == m_cdr[MSG_TYPE].compare("SMS_MO")) {
        return SMS_MO;
    }
    if (0 == m_cdr[MSG_TYPE].compare("SMS_MT")) {
        return SMS_MT;
    }
    if (0 == m_cdr[MSG_TYPE].compare("D")) {
        return D;
    }
    if (0 == m_cdr[MSG_TYPE].compare("U")) {
        return U;
    }
    if (0 == m_cdr[MSG_TYPE].compare("B")) {
        return B;
    }
    if (0 == m_cdr[MSG_TYPE].compare("X")) {
        return X;
    }
}

}// namespace wasc