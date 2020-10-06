#ifndef _TO_DO_PARSE_H_
#define _TO_DO_PARSE_H_
#include <string>
#include <fstream>
#include <iostream>
#include "runnable.hpp"
#include "cyc_waitable_queue.hpp"
#include "parser.hpp"
#include <fstream>
#include <vector>

namespace experis
{

class FileParse : public Runnable
{

    typedef std::string imsi;
    typedef std::string* Message;

public:
     FileParse(std::ifstream* a_file, WaitableQueue<std::string>* a_stringQueue);
    ~FileParse(){}
    virtual void Run();

private:
    FileParse(FileParse &a_other);
    FileParse &operator=(FileParse &a_other);

    std::ifstream *m_fd;
    Parser m_parser;
    Message* m_msgPtr;
    WaitableQueue<std::string>* m_stringQueue;
};

} // namespace experis

#endif // _TO_DO_PARSE_H_