#ifndef _THREAD_HPP_
#define _THREAD_HPP_

#include "runnable.hpp"
#include <semaphore.h>
#include <pthread.h> // pthread_t

namespace experis{

class Thread{
public:
    Thread(Runnable *a_run);
    virtual ~Thread();
    //Thread(const Thread& a_other)=deaf;

private:
    void DoWork();
    static void *StartWork(void *a_obj);
    Thread &operator=(const Thread &a_other);
private:
    pthread_t m_id;
    Runnable *m_run;
};

} // namespace experis

#endif /* _THREAD_HPP_ */
