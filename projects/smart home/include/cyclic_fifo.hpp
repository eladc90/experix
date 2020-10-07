#ifndef CYCLIC_FIFO_HPP
#define CYCLIC_FIFO_HPP
#include <queue>
#include <cstddef>

namespace smartHome {

template <class T>
//require T: CCtor and assinable
class CyclicFifo {
    
//! @brief Create a Generic data type Queue of a given size
//* The Queue is heap allocated and wraps around


    typedef std::queue<T> CyclitCont;

public:
    //!@brief CTOR of the cycclic  queue  
    //!@param[in] a_capacity - the max number of elements in the queue
    CyclicFifo(size_t a_capacity);
    ~CyclicFifo();

    //!@brief insert a new element to the queue 
    //!@param[in] a_val - value to insert the queue
    //!@retval bool - return false if the queue is full or true if insert successfully to queue
    bool Enqueue(T a_val);

    //!@brief remove Element the queue  
    //!@param[in] a_val - pointer to store the removed element
    //!@retval bool - return false if the queue is mpty or true if remove successfully from queue
    bool Dequeue(T* a_retVal);

    //!@brief return if the queue is empty or not
    bool IsEmpty() const NOEXCEPTIONS;

    //!@brief return the size of the queue 
    size_t GetSize() const NOEXCEPTIONS;

    //!@brief return the capacity of the queue 
    size_t GetCapacity() const NOEXCEPTIONS;

private:
    size_t m_capacity;
    CyclitCont m_cyclicFifo;
};

#include "inl/cyclic_fifo.hxx"

}// smartHome

#endif // !CYCLIC_FIFO_HPP