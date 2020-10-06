#include <iostream>
#include <exception>

template <class T>
CyclicFifo<T>::CyclicFifo(size_t a_capacity) 
    : m_capacity(a_capacity)
    , m_cyclicFifo()
{
}

template <class T>
CyclicFifo<T>::~CyclicFifo() 
{
}

template <class T>
bool CyclicFifo<T>::Enqueue(T a_val) {
    if (m_cyclicFifo.size() >= m_capacity) {
        return false;
    }
    m_cyclicFifo.push(a_val);
    return true;
}

template <class T>
bool CyclicFifo<T>::Dequeue(T* a_retVal) {
    if (IsEmpty()) {
        return false;
    }
    *a_retVal = m_cyclicFifo.front();
    m_cyclicFifo.pop();
    return true;
}

template <class T>
bool CyclicFifo<T>::IsEmpty() const NOEXCEPTIONS{
    return m_cyclicFifo.empty();
}

template <class T>
size_t CyclicFifo<T>::GetSize() const NOEXCEPTIONS{
    return m_cyclicFifo.size();
}

template <class T>
size_t CyclicFifo<T>::GetCapacity() const NOEXCEPTIONS{
    return m_capacity;
}

