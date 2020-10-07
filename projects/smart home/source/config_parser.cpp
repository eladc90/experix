#include "config_parser.hpp"
#include <iostream>

namespace smartHome {


ConfigParser::ConfigParser()
    : m_parseCont() 
{
}

void ConfigParser::ParseLine(std::string a_line) {
    m_parseCont.clear();
    std::string delimiter = ":";
    size_t pos = 0;
    std::string val;
    while ((pos = a_line.find(delimiter)) != std::string::npos) {
        val = a_line.substr(0, pos);
        m_parseCont.push_back(val);
        a_line.erase(0, pos + delimiter.length());
    }
    m_parseCont.push_back(a_line);
}

std::string ConfigParser::GetFunc() {
    return m_parseCont[CREATE_FUNC];
}

std::string ConfigParser::GetRoom() {
    return m_parseCont[ROOM];
}

std::string ConfigParser::GetFloor() {
    return m_parseCont[FLOOR];
}

}//smartHome