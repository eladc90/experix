
#include <assert.h>
#include "operator_aggregator.hpp"
#include <iostream>
#include <unistd.h>
#include "mobile_operator.hpp"

static const int numOfElem = 10;

namespace experis
{

OperatorAggregator::OperatorAggregator(CdrDispatcher* a_dispatcher)
: IAggregator(a_dispatcher)
, m_operatorContainer(numOfElem,Functor(),0)
{
}



void OperatorAggregator::Aggregate(Cdr *a_cdr){ 
    
    MobileOperator mobOp(a_cdr);

    std::cout<<" Operator Agg Base Got Mobile_company "<<a_cdr->GetMNS()<<std::endl;	 
    m_operatorContainer.Update(a_cdr->GetMNS(),mobOp);
}



OperatorAggregator::~OperatorAggregator(){

std::cout<<"Dtor Operator_Aggregator"<<std::endl;

}


}//namespace





/*
MobileOperator* OperatorAggregator::GetRecord(const std::string &a_key ,QUERY_REQWEST a_reqType ){

    assert( OPREATOR_RETRIVE == a_reqType);   // for now , here there is only one type
    try
    {
       return m_operatorContainer.Get(a_key);
    }
    catch (std::out_of_range)
    {
        return 0;  // throw 
    }

}
*/