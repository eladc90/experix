#ifndef _CDRDISPATCHER_HPP_
#define _CDRDISPATCHER_HPP_

#include <vector>
#include "aggregator.hpp"
#include "cdr.hpp"
#include <stddef.h>
#include "runnable.hpp"
#include <iostream>

namespace experis{


class CdrDispatcher{

public:
     CdrDispatcher();
    ~CdrDispatcher();
    void Dispatch(Cdr* a_cdr);
    void Subscribe(IAggregator* a_subscriber);

private:
    typedef std::vector<IAggregator*> AggregatorContainer;
    CdrDispatcher(const CdrDispatcher& a_other);
    CdrDispatcher& operator=(const CdrDispatcher& a_other);
    AggregatorContainer m_allAggs;
};


class RunDisp : public Runnable{

public:
    RunDisp(Cdr* a_cdr, CdrDispatcher* a_disp):m_cdr(a_cdr),m_dispathcer(a_disp){}
    
    virtual void Run(){
            m_dispathcer->Dispatch(m_cdr);
        }  
private:
    CdrDispatcher* m_dispathcer;
    Cdr* m_cdr;
};


} // namespace experis

#endif // _CDRDISPATCHER_HPP_
