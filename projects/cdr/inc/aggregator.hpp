#ifndef __AGGREGATOR_HPP__
#define __AGGREGATOR_HPP__

#include "cdr.hpp"


namespace experis {

class CdrDispatcher;



class IAggregator{


public:
    IAggregator(CdrDispatcher* a_dispatcher);
    virtual ~IAggregator()=0;
    virtual void Aggregate(Cdr* a_cdr)=0;
    
private:
    IAggregator(const IAggregator& a_other);
    IAggregator& operator=(const IAggregator& a_other);

    CdrDispatcher* m_disp;  //for future run time options 

};

}// experis

#endif //__AGGREGATOR_HPP__
