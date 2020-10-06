#ifndef __MUTEX_HPP__
#define __MUTEX_HPP__

#include <pthread.h>
#include "uncopyable.hpp"
#include "common_utils.hpp"

namespace smartHome{

class ConditionVar;

class Mutex : private Uncopyable{

public:
    Mutex();
    ~Mutex() NOEXCEPTIONS;

    void Lock() ;
    void UnLock() ;

protected:
    //template <class Predicate>
    //friend  void ConditionVar::Wait(Mutex& a_mutex, Predicate* a_condition);
    friend class ConditionVar;
    pthread_mutex_t* GetNativeMutex() { return &m_mutex; }
    
private:
    bool TryInitAgain();
    void mutexInit();
    pthread_mutex_t m_mutex;
};

} // namespace smartHome

#endif /* __MUTEX_HPP__ */