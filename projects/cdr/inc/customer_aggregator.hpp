#ifndef __CUSTOMER_AGGREGATOR_HPP__
#define __CUSTOMER_AGGREGATOR_HPP__

#include <string>
#include <vector>
#include "cdr.hpp"
#include "aggregator.hpp"
#include "customer.hpp"
#include "query.hpp"
#include "record.hpp"
#include "functor.hpp"
#include "hash_mt.hpp"
#include "update_functor.hpp"
#include "hashFunc.hpp"

namespace experis {

class IAggregator;

class CustomerAggregator : public IAggregator, public IQuery {

    typedef std::string KEY;

public:
    CustomerAggregator(CdrDispatcher* a_dispatcher);
    virtual ~CustomerAggregator();
    virtual void Aggregate(Cdr * a_cdr);
    //virtual Customer* GetRecord(const std::string& a_key , QUERY_REQWEST a_reqType);
    
private:
    CustomerAggregator(const CustomerAggregator& a_other);
    CustomerAggregator& operator=(const CustomerAggregator& a_other);

    HashMT<KEY ,Customer ,Functor ,Customer>  m_hash;

};
}// experis

#endif //__CUSTOMER_AGGREGATOR_HPP__