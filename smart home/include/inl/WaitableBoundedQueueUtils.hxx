#ifndef WAITABLE_BOUNDED_QUEUE_UTILS
#define WAITABLE_BOUNDED_QUEUE_UTILS
#include <cstdlib>
#include "mutex.hpp"
#include "cyclic_fifo.hpp"


namespace smartHome {

template<class ValType>
class QueuePredicate{
public:
    QueuePredicate() {}
    virtual ~QueuePredicate(){};
    
    virtual bool operator()() = 0;
private:

};

/*------------ is queue full predicator -------------*/

template<class ValType>
class IsQueueFull : public QueuePredicate<ValType>{
public:
    IsQueueFull(const WaitableBoundedQueue<ValType>& a_waitableQueue);
    ~IsQueueFull();
    bool operator()();
private:
    const WaitableBoundedQueue<ValType>& m_waitableQueue;
};

template<class ValType>
IsQueueFull<ValType>::IsQueueFull(const WaitableBoundedQueue<ValType>& a_waitableQueue) 
    : m_waitableQueue(a_waitableQueue)
{
}

template<class ValType>
IsQueueFull<ValType>::~IsQueueFull() 
{
}

template<class ValType>
bool IsQueueFull<ValType>::operator()() {
    if (m_waitableQueue.IsShutDown()) {
        return false;
    }
    return m_waitableQueue.NotSafeSize() >= m_waitableQueue.NotSafeCapacity();
}

/*------------ is queue empty predicator -------------*/

template<class ValType>
class IsQueueEmpty : public QueuePredicate<ValType> {
public:
    IsQueueEmpty(const WaitableBoundedQueue<ValType>& a_waitableQueue);
    ~IsQueueEmpty();
    bool operator()();
private:
    const WaitableBoundedQueue<ValType>& m_waitableQueue;
};

template<class ValType>
IsQueueEmpty<ValType>::IsQueueEmpty(const WaitableBoundedQueue<ValType>& a_waitableQueue) 
    : m_waitableQueue(a_waitableQueue)
{
}

template<class ValType>
IsQueueEmpty<ValType>::~IsQueueEmpty() 
{
}

template<class ValType>
bool IsQueueEmpty<ValType>::operator()() {
    if (m_waitableQueue.IsShutDown()) {
        return false;
    }
    return m_waitableQueue.NotSafeSize() == 0;
}

struct QueueShutDown : public std::exception {

    virtual const char* what() const throw()
    {
      return ("the queue is shut down!");
    }
};

#endif // !WAITABLE_BOUNDED_QUEUE_UTILS
    
} // namespcae smartHome