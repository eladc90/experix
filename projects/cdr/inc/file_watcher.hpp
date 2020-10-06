#ifndef __FILE_WATCHER_HPP__
#define __FILE_WATCHER_HPP__
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <limits.h>
#include <unistd.h> //read
#include <string>
#include "cyc_waitable_queue.hpp"
#include "runnable.hpp"

namespace experis{

class FileWatcher :public Runnable {
public:
    //throw run_time change to our exception
    FileWatcher(const char* a_root, experis::WaitableQueue<std::string>* a_nameQ);
    ~FileWatcher() {}
    //throw run_time change to our exception
    void Run();

private:
    FileWatcher(const FileWatcher& a_mod);
    FileWatcher operator=(const FileWatcher& a_mod);

    int m_fd;
    int m_wd;
    experis::WaitableQueue<std::string>* m_filesNames;
}; //IsMod    

}// experis






#endif //__FILE_WATCHER_HPP__
