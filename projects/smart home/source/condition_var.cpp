#include <pthread.h>
#include <cerrno>
#include <iostream>
#include <unistd.h>
#include <assert.h>
#include "condition_var.hpp"
#include "condition_var_exception.hpp"

namespace smartHome{

ConditionVar::ConditionVar() {
    int initStatus = pthread_cond_init(&m_condVar,0);

    if(0 != initStatus){
        switch(initStatus) {
            case EAGAIN:
                if(!TryInitAgain()) {
                    throw InitNoResourcesException();
                }
                break;
            case ENOMEM:
                throw InitNoResourcesException(); 
                break;
            case EBUSY:
                assert(!"Ctor Error");
                break;
            case EINVAL:
                assert(!"Ctor Error");
                break;
        }
    }
}

ConditionVar::~ConditionVar() NOEXCEPTIONS {
    while(0 != pthread_cond_destroy(&m_condVar)) {
        NotifyAll();
    }
}

void ConditionVar::SignalOne() NOEXCEPTIONS {

    if (0 != pthread_cond_signal(&m_condVar)) {
        assert(!"pthread_cond_signal error");//TODO
    } 
}

void ConditionVar::NotifyAll() NOEXCEPTIONS {

      if (0 != pthread_cond_broadcast(&m_condVar)) {
        assert(!"pthread_cond_broadcast error");//TODO
    }   
}

bool ConditionVar::TryInitAgain(){ 
    size_t initTry = 3;
    unsigned int waitTime = 4 * 1000; // TODO
    int initStatus = 1;

    while(0 != initTry && 0 != initStatus) 
    {
        initStatus = pthread_cond_init(&m_condVar,0);
        if(!initStatus) {
            break;
        }
        usleep(waitTime);
        --initTry;
        waitTime *= 2;
    }
    return !initStatus;
}


}//smartHome
