#include <iostream>
#include "thread_pool.hpp"
#include "task_consumer.hpp"
#include "runnable.hpp"
#include "thread.hpp"
#include "poision_apple.hpp"
#include "mutex.hpp"

namespace smartHome {

TreadPool::TreadPool(size_t a_capacity, size_t a_numOfThread)
    :m_tasks(a_capacity)
    ,m_taskConsumer(new TaskConsumer(m_tasks))
    ,m_threads() {
    AddThread(a_numOfThread);
}

TreadPool::~TreadPool() {
    //ShutDown();
}

void TreadPool::AddTask(SharedPtr<Runnable> const& a_task) {
    m_tasks.Enqueue(a_task);

} 

void TreadPool::AddThread(size_t a_numOfThreads) {
    
    for (size_t i = 0; i < a_numOfThreads; ++i) {        
        m_threads.InsertThread(SharedPtr<Thread>(new Thread(*(m_taskConsumer))));
    }
}

void TreadPool::RemoveThread(size_t a_numOfThread) {
    for (size_t i = 0; i < a_numOfThread; ++i) {
        SharedPtr<Runnable> poisApp(new PoisionApple);
        m_tasks.Enqueue(poisApp);
    }
}

bool TreadPool::ShutDown(size_t a_timeInMicroSec) {
    MutexGuard mutexGrd(m_mutex);
    if (a_timeInMicroSec == 0) {
        RemoveThread(m_threads.Size());
        JoinThreads();
        return true;
    }
    return m_threads.TimedJoinAll(a_timeInMicroSec);
}

void TreadPool::JoinThreads() {
    m_threads.JoinAll();
    
}

void TreadPool::ShutDownImediate() {
    MutexGuard mutexGrd(m_mutex);
    m_threads.CancelAll();
}

}//smartHome