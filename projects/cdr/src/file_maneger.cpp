#include "file_maneger.hpp" 
#include <iostream>
namespace experis {

std::ifstream* FileMng::GetNewFile() {
    std::ifstream* fd = m_fileCont.front(); 
    m_fileCont.pop();
    return fd;
}

void FileMng::AddFile(std::ifstream* a_file) {
    m_fileCont.push(a_file);
}

} //experis