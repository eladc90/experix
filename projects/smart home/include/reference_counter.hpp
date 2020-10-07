#ifndef REFERENCE_COUNT_HPP_
#define REFERENCE_COUNT_HPP_

#include <signal.h> 
#include <stdio.h> 
#include <cstddef>   

namespace smartHome {

template<class FUNCTOR>
class RefCount {

    typedef sig_atomic_t COUNTER; 
    
    template <class OTHER>
    friend class RefCount;
public:
    explicit RefCount(FUNCTOR a_deleteFunc);
    template<class OTHER>
    RefCount(const RefCount<OTHER>& a_other);
    ~RefCount();
    RefCount(const RefCount& a_other); // cctor
    RefCount& operator=(const RefCount& a_other);

    COUNTER* Get() const { return m_counter; }
    RefCount& operator++(); 
    RefCount& operator--();
    COUNTER operator*() { return *m_counter; }
    operator bool(){ return (*m_counter) != 0; }
    
private:
    COUNTER* increaceRefCount(COUNTER* a_other);
    void decreaseAndTerminate();

    COUNTER* m_counter;
    FUNCTOR m_deleteFunc;
};

#include "inl/reference_counter_inl.hpp"

}//namespce smartHome

#endif // REFERENCE_COUNT_HPP_

