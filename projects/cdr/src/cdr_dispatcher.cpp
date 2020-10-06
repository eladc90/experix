
#include <iostream>
#include <stdexcept>
#include <utility>
#include "cdr_dispatcher.hpp"
#include <unistd.h>
namespace experis
{



CdrDispatcher::CdrDispatcher()
: m_allAggs()
{
}

CdrDispatcher::~CdrDispatcher(){

}

void CdrDispatcher::Dispatch(Cdr *a_cdr)
{

    for (int i = 0; i < m_allAggs.size(); ++i)
    {
        std::cout<<" Aggregator "<<(i+1)<<" Get new Cdr from Thread " << std::endl;
        
        (m_allAggs)[i]->Aggregate(a_cdr);
    }

    delete a_cdr;
}

 void CdrDispatcher::Subscribe(IAggregator* a_subscriber){

     m_allAggs.push_back(a_subscriber);
     std::cout<<" Agg Subscribed "<< std::endl;
 }

} // namespace experis
