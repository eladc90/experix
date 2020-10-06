#ifndef THREAD_H_
#define THREAD_H_
#include <pthread.h>
#include "runnable.hpp"

namespace smartHome {

class Thread {
public: 
    Thread(Runnable& a_run);
    Thread(const Thread& a_thread);
    ~Thread();
    void Detach();
    void Join();
    bool TimedJoin(const timespec& a_timeToJoin);
    void Cancel();
    void Exit();
private:
    static void* CallDo(void* a_thread);
    Thread& operator=(const Thread& a_thread);
    void DoWork();

    Runnable& m_run;
    pthread_t m_threadID;
    int m_joinSts;
};

}// smartHome

#endif //THREAD_H_