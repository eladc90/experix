#include <string>
#include <algorithm>
#include <cstring>
#include "parser.hpp"
#include <string>
#include <iostream>

namespace experis {

static const int CDR_SIZE = 11;

Parser::Parser(){}

Parser::Msg Parser::BuildMsg(std::string& a_msg) {
    size_t from = 0;
    size_t to = 0;
    int i = 0;
    Msg msgArr = new std::string[CDR_SIZE];
    size_t len = strlen(a_msg.c_str());
    while( to < len ) {
        to = a_msg.find_first_of("|", from);
        msgArr[i] = a_msg.substr(from, to - from);
        from = to + 1;
        ++i;
            std::cout<<"this is parser build func"<<msgArr[0]<<std::endl;
    }
    


    return msgArr;
}

}// namespace wasc
