#include <exception>
#include <string>
#include <assert.h>
#include "customer_aggregator.hpp"
#include "customer.hpp"
#include "cdr_dispatcher.hpp"

static const int numOfElem = 200;


namespace experis {


    CustomerAggregator::CustomerAggregator(CdrDispatcher* a_dispatcher)
    : IAggregator(a_dispatcher)
    , m_hash(numOfElem,Functor(),0)
    {
    }

    CustomerAggregator::~CustomerAggregator(){

        std::cout<<"Dtor Customer_Aggregator"<<std::endl;
    }

    void CustomerAggregator::Aggregate(Cdr* a_cdr){

        Customer cust(a_cdr);
        std::cout<<" Customer Agg Base Got Client_Num "<<a_cdr->GetImsi()<<std::endl;	 
        m_hash.Update(a_cdr->GetImsi(),cust);
    }


}// experis namespace

