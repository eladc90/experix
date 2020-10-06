#include <string>
#include <sys/inotify.h> //INOTIFY
#include <iostream> //debug
#include <fstream>
#include <stdexcept>
#include <errno.h>
#include <unistd.h>
#include "file_watcher.hpp"
#define DEBUG 

namespace experis{

static const int FAIL = -1;
static const unsigned int MAX_NAME_LEN = 20; 
static const size_t EVENT_SIZE =  sizeof(struct inotify_event);
static const unsigned int MAX_EVENT =  1024;
static const size_t BUFFER_LEN = ( MAX_EVENT * (EVENT_SIZE + MAX_NAME_LEN) );
static const uint32_t WATCH_FLAGS = (IN_MOVED_TO | IN_CLOSE_NOWRITE | IN_DELETE | IN_CLOSE_WRITE);
static const char* DONE_DIR_PATH = "../done/";
static const char* FROM_DIR_PATH = "../test_dir/";

FileWatcher::FileWatcher(const char* a_root, experis::WaitableQueue<std::string>* a_nameQ)
    : m_filesNames(a_nameQ)
{
    m_fd = inotify_init ();
    if(FAIL == m_fd){
        throw std::runtime_error("Couldn't initialize inotify");
    }
    std::cout << a_root << std::endl;
    m_wd = inotify_add_watch(m_fd, a_root, WATCH_FLAGS);
    if(FAIL == m_wd){
        throw std::runtime_error("Couldn't add watch to the path given");
    }
}

void FileWatcher::Run() {

    int length = 0;
    int i = 0;
    char eventBuff[BUFFER_LEN];
    unsigned eventNum = 0;
    std::string res;
    
    while (1){
        i = 0;
        length = read(m_fd, eventBuff, BUFFER_LEN);
        if(length == FAIL) {
            throw std::runtime_error("reading failed, extend");
        }
        
        while(i < length) {
            struct inotify_event *event = ( struct inotify_event * ) &eventBuff[i];

            // create
            if (0 != (event->mask & IN_MOVED_TO)) {
                if (event->mask & IN_ISDIR) {
                    std::cout << "The directory "<< event->name << " was Created" << std::endl;       
                } 
                else
                {
                    std::cout<< "The file " <<  event->name << 
                    " was Created with WD " << event->wd << 
                    " and push to queue " << std::endl; 
                    m_filesNames->Enqueue(event->name);
                }
/*                     #ifdef DEBUG
                        m_filesNames->Dequeue(&res);
                        std::cout<< res << std::endl;
                    #endif */     
            }

            // delete (need to remove the file from queue now not relevent)
            else if(event->mask & IN_DELETE) {
                if (event->mask & IN_ISDIR) {
                    std::cout << "The directory " << event->name <<" was deleted" << std::endl;       
                }
                else { 
                   std::cout << "The file "<< event->name << " was deleted with WD " << event->wd << std::endl;       
                }
            }

            else if(event->mask & IN_CLOSE_NOWRITE ) {
                if (event->mask & IN_ISDIR) {
                    std::cout << "The file "<< event->name << " finish! moved to done directory" << std::endl;
                    std::string to(DONE_DIR_PATH);
                    std::string from(FROM_DIR_PATH);
                    from += event->name;
                    to += event->name;
                    std::rename(from.c_str(), to.c_str());
                }
                
            } 

            i += EVENT_SIZE + event->len;
        }
    }
    inotify_rm_watch(m_fd, m_wd);
    close(m_fd);
}

}//experis
