#include <pthread.h>
#include <cassert>
#include <iostream>
#include <errno.h>
#include "thread.hpp"
#include "runnable.hpp"

namespace smartHome {

Thread::Thread(Runnable& a_run)
    : m_run(a_run) 
    ,m_joinSts(false) {
    if (0 != pthread_create(&m_threadID, NULL, CallDo, this)) {
        throw; 
    }
}

Thread::Thread(const Thread& a_thread)
    :m_run(a_thread.m_run) {
    if (0 != pthread_create(&m_threadID, NULL, CallDo, this)) {
        throw; 
    }
}

Thread::~Thread() {
    if(!m_joinSts)
    {
        Join();
    }
}

void Thread::Join() {
    if (m_joinSts) {
        return;
    }
    int joinStatus  = pthread_join(m_threadID, 0);
    
    if(joinStatus)
    {
        switch (joinStatus)
        {
        case EDEADLK:
            assert(!"A deadlock was detected.");
            break;

        default: assert(!"non doucument pthread join error");
            break;
        }
    } 
    m_joinSts = true;
} 

void Thread::Detach()
{
    if (m_joinSts) {
        return;
    }
    int detachStatus  = pthread_detach(m_threadID);
    
    if(detachStatus)
    {
        switch (detachStatus)
        {
        case ESRCH:
            assert(!"No thread with the ID thread could be found");
            break;
        case EINVAL:
            assert(!"thread is not a joinable thread");
        default: assert(!"non doucument pthread join error");
            break;
        }
    }  
    m_joinSts = true;
}

void* Thread::CallDo(void* a_thread) {
    assert(a_thread);
    Thread* thread = reinterpret_cast<Thread*>(a_thread);
    try {
        thread->DoWork();
    }
    catch(std::exception ex) {
        std::cerr << ex.what();
        assert(!"the runnable is not safe!");
    }
    catch (...) {
        assert(false);
    }
    return 0;
}

bool Thread::TimedJoin(const timespec& a_timeToJoin) {
    int timedJoinStst = pthread_timedjoin_np(m_threadID, 0 , &a_timeToJoin);
    switch(timedJoinStst) {
        case EBUSY:
        case ETIMEDOUT:
            return false;
        
        case EINVAL:
            assert(!"another thread wait to join this thread");

    }
    
    m_joinSts = true;
    return true;
}
void Thread::Cancel() {
    int cancelSts = pthread_cancel(m_threadID);
    switch (cancelSts) {
        case ESRCH:
            assert(!"No thread with this thread ID could be found.");
    }
    m_joinSts = true;
}
void Thread::Exit() {
    m_joinSts = true;
    pthread_exit(0);
}

void Thread::DoWork() {
    m_run.Run();
}

}//smartHome