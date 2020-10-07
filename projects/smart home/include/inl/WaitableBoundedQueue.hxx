#include <exception>
#include <iostream>
#include <string>
#include <vector>
#include "WaitableBoundedQueueUtils.hxx"
#include "WaitableBoundedQueue.hpp"


namespace smartHome {

template<class ValType, class QUEUE>
WaitableBoundedQueue<ValType, QUEUE>::WaitableBoundedQueue(size_t a_capacity)
    : m_mutex()
    , m_isDestroyed(false)
    , m_condVar()
    , m_queue(a_capacity)
{
}


template<class ValType, class QUEUE>
WaitableBoundedQueue<ValType, QUEUE >::~WaitableBoundedQueue() NOEXCEPTIONS{
    TurnOnIsShutDown();
    m_condVar.NotifyAll();


}

template<class ValType, class QUEUE>
void WaitableBoundedQueue<ValType, QUEUE >::Enqueue(ValType a_value){
    SignalGuard signalGuard(m_condVar);
    {
        MutexGuard mutexGuard(m_mutex);
        IsQueueFull<ValType> predicate(*this);
   
        AccessQueue(&predicate);
        m_queue.Enqueue(a_value);                         
    }
    signalGuard.NotifyOne();
}

template<class ValType, class QUEUE>
void WaitableBoundedQueue<ValType, QUEUE >::Dequeue(ValType& a_value){
    SignalGuard signalGuard(m_condVar);
    {
        MutexGuard mutexGuard(m_mutex);
        IsQueueEmpty<ValType> predicate(*this);
        
        AccessQueue(&predicate);
        m_queue.Dequeue(&a_value); 
    }
    signalGuard.NotifyOne();
    
}



template<class ValType, class QUEUE>
bool WaitableBoundedQueue<ValType, QUEUE >::IsEmpty()const NOEXCEPTIONS {
    MutexGuard mutexGuard(m_mutex);
    return m_queue.IsEmpty();
} 
template<class ValType, class QUEUE>
size_t WaitableBoundedQueue<ValType, QUEUE >::Size()const NOEXCEPTIONS {
    return m_queue.GetSize();
}

template<class ValType, class QUEUE>
void WaitableBoundedQueue<ValType, QUEUE >::ShutDown() {
        
}

/*-------------- private functions ------------*/

template<class ValType, class QUEUE>
size_t WaitableBoundedQueue<ValType, QUEUE >::NotSafeSize()const NOEXCEPTIONS{
    return m_queue.GetSize();
}

template<class ValType, class QUEUE>
size_t WaitableBoundedQueue<ValType, QUEUE >::NotSafeCapacity()const NOEXCEPTIONS{
    return m_queue.GetCapacity();
}

template<class ValType, class QUEUE>
void WaitableBoundedQueue<ValType, QUEUE >::TurnOnIsShutDown() {
    m_isDestroyed = true;
}

template<class ValType, class QUEUE>
void WaitableBoundedQueue<ValType, QUEUE >::AccessQueue(QueuePredicate<ValType>* a_predicate) {
    m_condVar.Wait<QueuePredicate<ValType> >(m_mutex, a_predicate);
    if(m_isDestroyed){
        throw QueueShutDown();
    }
}

template<class ValType, class QUEUE>
bool WaitableBoundedQueue<ValType, QUEUE >::IsShutDown()const{
    return m_isDestroyed;
}

}//namespace smartHome
