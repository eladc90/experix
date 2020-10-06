#include <fstream>
#include <iostream>
#include <string>
#include "../inc/to_do_parse.hpp"

namespace experis {

FileParse::FileParse(std::ifstream* a_file, WaitableQueue<std::string>* a_stringQueue) 
: m_fd(a_file)
, m_parser()
, m_msgPtr()
{

}
 
void FileParse::Run() {

    std::string line;
    while (!m_fd->eof()) {
        
        getline(*m_fd, line);
       *m_msgPtr = m_parser.BuildMsg(line);
        std::cout<<"this is To do func"<<line<<std::endl;

    }
}

}// wasc
