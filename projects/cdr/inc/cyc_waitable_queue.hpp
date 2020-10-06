#ifndef __WAITABLEQUEUE_HPP__
#define __WAITABLEQUEUE_HPP__

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <queue>
#include <vector>
#include "mutex.hpp"
#include "conditional_variable.hpp"

#define DEBUG

namespace experis{
    
template<typename ValType>
class WaitableQueue{

public:
    WaitableQueue(size_t a_capacity);
    ~WaitableQueue();
    void Enqueue(ValType a_value);
    void Dequeue(ValType* a_value);
    bool IsEmpty()const;    
    size_t Size()const;

private:
    WaitableQueue(const WaitableQueue & a_other);
    WaitableQueue& operator=(const WaitableQueue & a_other);

private:
    Mutex m_mutex;
    bool m_isDestroyed;
    size_t m_capacity;
    size_t m_waitingsNumber;
    ConditionalVariable m_condVar;
   // ConditionalVariable m_notEmpty;
    std::queue<ValType> m_queue;
};

#include "cyc_waitable_queue_inl.hpp"

}//namespace experis

#endif /* _WAITABLEQUEUE_HPP_ */
