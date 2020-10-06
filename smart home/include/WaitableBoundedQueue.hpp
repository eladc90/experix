#ifndef __WAITABLEQUEUE_HPP__
#define __WAITABLEQUEUE_HPP__
#include <assert.h>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <queue>
#include "uncopyable.hpp"
#include "mutex.hpp"
#include "condition_var.hpp"
#include "cyclic_fifo.hpp"
#include "common_utils.hpp"

#define DEBUG

namespace smartHome{

template<typename ValType>
class QueuePredicate;

template<typename ValType>
class IsQueueFull;

template<typename ValType>
class IsQueueEmpty;

template<class ValType, class QUEUE = CyclicFifo<ValType> >
//require ValType: CCtor and assinable
//require QUEUE: has Enqueue(), Dequeue(), IsEmpty() , GetSize()
class WaitableBoundedQueue : private Uncopyable{

//! @brief Create a thread safe container in size of given capacity

    friend class IsQueueEmpty<ValType>;
    friend class IsQueueFull<ValType>;
public:
    //!@brief CTOR of thread safe container  
    //!@param[in] a_capacity - the max number of elements in the container
    WaitableBoundedQueue(size_t a_capacity);

    //!@brief DTOR of thread safe container   
    ~WaitableBoundedQueue() NOEXCEPTIONS;

    //!@brief insert a new element to the container 
    //!@param[in] a_val - value to insert the container
    void Enqueue(ValType a_value);

    
    //!@brief remove Element from the container  
    //!@param[in] a_val - pointer to store the removed element
    void Dequeue(ValType& a_value);

    //!@brief return if the container is empty or not (true == empty)  
    bool IsEmpty()const NOEXCEPTIONS;    

    //!@brief return the size of the container  
    size_t Size()const NOEXCEPTIONS;

    void ShutDown();

private:

    void TurnOnIsShutDown();
    void AccessQueue(QueuePredicate<ValType>* a_predicate);
    bool IsShutDown() const;
    size_t NotSafeSize()const NOEXCEPTIONS;
    size_t NotSafeCapacity()const NOEXCEPTIONS;


private:
    Mutex m_mutex;
    bool m_isDestroyed;
    ConditionVar m_condVar;
    QUEUE m_queue;
};

}//namespace smartHome

#include "inl/WaitableBoundedQueue.hxx"

#endif /* _WAITABLEQUEUE_HPP_ */
