#include "thread_container.hpp"
#include <iostream> //remove this 
namespace smartHome {

size_t MicroToNanoSec(size_t a_micro) {
    return a_micro * 1000;
}

ThreadContainer::ThreadContainer()
    : m_container()
    , m_mutex() 
{
}

ThreadContainer::~ThreadContainer() {
    m_container.clear();
}

void ThreadContainer::InsertThread(SharedPtr<Thread> a_thread) {
    MutexGuard mutex(m_mutex);
    m_container.push_back(a_thread);
}

void ThreadContainer::Clear() {
    MutexGuard mutex(m_mutex);
    m_container.clear();
}

size_t ThreadContainer::Size() {
    MutexGuard mutex(m_mutex);
    return m_container.size();
}

timespec ThreadContainer::InitTimeSpec() {
    timespec timeToShut;
    clockid_t realTime = CLOCK_MONOTONIC;
    clock_gettime(realTime, &timeToShut);
    return timeToShut;
}

void ThreadContainer::JoinAll() {   
    MutexGuard mutex(m_mutex);
    CONTAINER::iterator beginItr = m_container.begin();
    CONTAINER::iterator endItr = m_container.end();
    while (beginItr != endItr) {
        (*beginItr)->Join();
        ++beginItr;
    }
}

bool ThreadContainer::TimedJoinAll(size_t a_time) {   
    MutexGuard mutex(m_mutex);
    CONTAINER::iterator beginItr = m_container.begin();
    CONTAINER::iterator endItr = m_container.end();
    timespec timeToShutDown = InitTimeSpec();
    timeToShutDown.tv_nsec += MicroToNanoSec(a_time);
    while (beginItr != endItr) {
        if (false == (*beginItr)->TimedJoin(timeToShutDown)) {
            break;
        }
        ++beginItr;
    }
    if (beginItr == endItr) { 
        return true;
    }
    return false;
}

void ThreadContainer::CancelAll() {   
    MutexGuard mutex(m_mutex);
    CONTAINER::iterator beginItr = m_container.begin();
    CONTAINER::iterator endItr = m_container.end();
    while (beginItr != endItr) {
        (*beginItr)->Cancel();
        ++beginItr;
    }
}

void ThreadContainer::ExitAll() {   
    MutexGuard mutex(m_mutex);
    CONTAINER::iterator beginItr = m_container.begin();
    CONTAINER::iterator endItr = m_container.end();
    while (beginItr != endItr) {
        (*beginItr)->Exit();
        ++beginItr;
    }
}

void ThreadContainer::DetachAll() {   
    MutexGuard mutex(m_mutex);
    CONTAINER::iterator beginItr = m_container.begin();
    CONTAINER::iterator endItr = m_container.end();
    while (beginItr != endItr) {
        (*beginItr)->Detach();
        ++beginItr;
    }
}

}// namespace smartHome