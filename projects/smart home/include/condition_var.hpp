#ifndef CONDITION_VAR_H_
#define CONDITION_VAR_H_
#include <iostream>
#include "mutex.hpp"
#include "uncopyable.hpp"

namespace smartHome {

class ConditionVar : private Uncopyable {

public:
    ConditionVar();
    ~ConditionVar() NOEXCEPTIONS;

    void NotifyAll() NOEXCEPTIONS;
    void SignalOne() NOEXCEPTIONS;

    template <class Predicate>
    // Predicate has bool operator()()
    //nullary boolean function object or function
    void Wait(Mutex& a_mutex, Predicate* a_condition); 
    
private:
    bool TryInitAgain();
    pthread_cond_t m_condVar;
};

template <class Predicate>
void ConditionVar::Wait(Mutex& a_mutex, Predicate* a_condition) {
    while((*a_condition)()) {
        pthread_cond_wait(&m_condVar, a_mutex.GetNativeMutex());
    }
}

}//smartHome

#endif //CONDITION_VAR_H_