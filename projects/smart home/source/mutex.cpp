#include <pthread.h>
#include <exception>
#include <errno.h> //value return from mutex
#include <cassert>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "mutex.hpp"
#include "mutex_exception.hpp"

namespace smartHome{


static unsigned long MiliToMicro(unsigned int a_miliSecond) {
    return a_miliSecond * 1000;
}

Mutex::Mutex(){
    mutexInit();
}

void Mutex::mutexInit(){

    int initStatus = pthread_mutex_init(& m_mutex, 0);
    switch (initStatus)
    {
        case EAGAIN:
            if(TryInitAgain() == false) 
            {
                throw(EAGAINMutexInit());
            }
            break;
        case ENOMEM:
            throw(ENOMEMMutexInit());
            break;
        
        
        case EPERM:
            assert(!" initialize error. caller doesnt have privileges");
            break;
        
        case EINVAL:
            assert(!"initialize error: value is invalid");
        
        case EBUSY:
            assert(!"attempt to reinitialise mutex");
            break;

        default:
            break;
    }
}

Mutex::~Mutex() NOEXCEPTIONS{
    int destroyStatus = pthread_mutex_destroy(& m_mutex);
    switch (destroyStatus) {
        case EBUSY:
            assert(!"mutex dtor error: trying to destroy while still in use");
            break;
        case EINVAL:
            assert(!"Dtor error: mutex value is invalid");
        break;
    }
}

void Mutex::Lock() {
    int lockStatus = pthread_mutex_lock(& m_mutex);
    switch (lockStatus)
    {
        case EINVAL:
            assert(!"Mutex lock error: invalid value");
            break;
        case EAGAIN:
            throw(MutexlockEAGAIN());
            break;

        case EDEADLK:
            throw(EDEADLKMutexlock());
            break;
        
        default:
            break;
    }
}

void Mutex::UnLock() {
    int retval = pthread_mutex_unlock(& m_mutex);
    switch (retval)
    {
        case EPERM:
            throw(EPERMMutexUnlock());
            break;
        
        case EAGAIN:
            throw(MutexUnlockEAGAIN());

        case EINVAL:
            assert(!"Mutex unlock error: The value specified by mutex does not refer to an initialized mutex object");
            break;

        default:
            break;
    }
}

bool Mutex::TryInitAgain() {
    size_t initTry = 3;
    unsigned int waitTime = MiliToMicro(4); 
    int initStatus = 1;

    while(0 != initTry) 
    {
        initStatus = pthread_mutex_init(& m_mutex, 0);
        if(!initStatus) {
            break;
        }
        usleep(waitTime);
        --initTry;
        waitTime *= 2;
    }
    return !initStatus;
}

} //namespace smartHome