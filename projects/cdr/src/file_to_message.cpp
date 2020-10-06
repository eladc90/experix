#include <fstream>
#include <iostream>
#include <string>
#include "file_to_message.hpp"

namespace experis {

FileToMsg::FileToMsg(WaitableQueue<Message>* a_files , WaitableQueue<Message>* a_msg)
    : m_fd()
    , m_fileCont(a_files)
    , m_msgCont(a_msg)
{
    
}
 
void FileToMsg::Run() {

    std::string line;
    std::string fileName;
    while (1){ // for the deueue files
        m_fileCont->Dequeue(&fileName);
        std::cout<<"file : " << fileName << std::endl;
        m_fd.open("../test_dir/test_file", std::ifstream::in); // c_str or string??

        while (getline(m_fd, line)) {
            m_msgCont->Enqueue(line);
            std::cout<<"line : " << line << std::endl;
        }
        std::cout<<"finish : " << fileName << std::endl;

        m_fd.close();
    }
}

}// experis
