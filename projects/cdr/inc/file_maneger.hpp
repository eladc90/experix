#ifndef _FILE_MANEGER_H
#define _FILE_MANEGER_H
#include <queue>
#include <fstream>

namespace experis {

    
class FileMng { 
typedef std::queue<std::ifstream*> FileCont;

public:
    FileMng() {}
    ~FileMng() {}

    std::ifstream* GetNewFile();
    void AddFile(std::ifstream* a_file);
    bool IsEmpty() { return m_fileCont.empty(); } 

private:
    FileMng(FileMng& a_other);
    FileMng& operator=(FileMng& a_other);

    FileCont m_fileCont;
};

}// experis

#endif // _FILE_MANEGER_H
