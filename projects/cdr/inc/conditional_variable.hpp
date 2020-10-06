#ifndef __CONDITIONALVARIABLE_HPP__
#define __CONDITIONALVARIABLE_HPP__

#include <pthread.h>
#include "mutex.hpp"
#include "condition_var_exception.hpp"
#include <cerrno>
#include <assert.h>
#include <cstdio>

namespace experis{

class Mutex;

class ConditionalVariable{

public:
    ConditionalVariable();
    ~ConditionalVariable();

    void Wait(Mutex* a_mutex);
    void Signal();        //one
    void Broadcast();    //all
  //  void Lock() {m_mutex.Lock();}
  //  void Unlock(){m_mutex.UnLock();}
 //   pthread_mutex_t GetMutex(){ return m_mutex.GetMutex();}

private:
    ConditionalVariable(const ConditionalVariable &a_other);
    ConditionalVariable &operator=(const ConditionalVariable &a_other);

private:

    pthread_cond_t m_condition;
    
};


} //namespace experis

#endif /* _CONDITIONALVARIABLE_HPP_ */








// case of Wait Template 
/*
template <typename Predicate>
void ConditionalVariable::Wait(const Predicate& a_predicate){

     while(a_predicate())
     {
        int sts = pthread_cond_wait(&m_condition, &m_mutex.GetMutex());
        if (0 != sts){
            if(sts== EINVAL){
                throw WaitInvalidException();
            }
            else if (sts== EPERM){
                throw WaitNotOwnException();
            }
            else{
                assert(!"pthread_cond_wait invalid error option");
            }
        }
    }
}
*/

