#ifndef __MUTEX_HPP__
#define __MUTEX_HPP__

#include <pthread.h>

namespace experis{

class Mutex{
    
public:
    Mutex();
    ~Mutex();
    //Mutex(const Mutex&)=deaf;
    //Mutex& operator=(const Mutex&)=deaf;

    void Lock();
    void UnLock();
    pthread_mutex_t &GetMutex();

private:
    void mutexInit();
    pthread_mutex_t m_mutex;
};

} // namespace experis

#endif /* __MUTEX_HPP__ */