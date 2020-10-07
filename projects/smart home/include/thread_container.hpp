#ifndef THREAD_CONTAINER
#define THREAD_CONTAINER
#include <vector>
#include<iostream> 
#include <algorithm> 
#include "uncopyable.hpp"
#include "mutex.hpp"
#include "common.hpp"
#include "thread.hpp"
#include "common_utils.hpp"

namespace smartHome {

typedef std::vector<SharedPtr<Thread> > CONTAINER;

class ThreadContainer : private Uncopyable{
public:    
    ThreadContainer();
    ~ThreadContainer();

    void InsertThread(SharedPtr<Thread> a_thread);
    void Clear();
    size_t Size();
    
    void JoinAll();
    void JoinThreads();
    bool TimedJoinAll(size_t a_time);
    void CancelAll();
    void ExitAll();
    void DetachAll();
    
private:
    timespec InitTimeSpec();
    template<class Func>
    void ForEach(Func* a_func); // TODO

private:
    CONTAINER m_container;
    Mutex m_mutex;

};

}// namespace smartHome

#endif //  THREAD_CONTAINER