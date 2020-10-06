#ifndef _FILE_TO_MESSAGE_HPP_
#define _FILE_TO_MESSAGE_HPP_

#include <string>
#include <iostream>
#include "runnable.hpp"
#include "cyc_waitable_queue.hpp"
#include <fstream>
#include <vector>

namespace experis
{

class FileToMsg : public Runnable
{
    typedef std::string Message;

public:
    FileToMsg(WaitableQueue<Message>* a_files ,WaitableQueue<Message>* a_msg);
    ~FileToMsg(){}
    virtual void Run();

private:
    FileToMsg(FileToMsg &a_other);
    FileToMsg &operator=(FileToMsg &a_other);

    std::ifstream m_fd;
    WaitableQueue<Message>* m_msgCont;
    WaitableQueue<Message>* m_fileCont;
};

} // namespace experis

#endif // _FILE_TO_MESSAGE_HPP_