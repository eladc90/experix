#ifndef _OPERTATOR_AGREGATOR_HPP_ 
#define _OPERTATOR_AGREGATOR_HPP_

#include <string>
#include <vector>
#include "cdr.hpp"
#include "hash_mt.hpp"
#include "aggregator.hpp"
#include "query.hpp"
#include "update_functor.hpp"
#include "hashFunc.hpp"
#include "cdr_dispatcher.hpp"

namespace experis {

class MobileOperator;

class OperatorAggregator: public IAggregator , public IQuery {

    typedef std::string Key;

public:
    OperatorAggregator(CdrDispatcher* a_dispatcher);
    ~OperatorAggregator();

public:
    virtual void Aggregate(Cdr * a_cdr);
    //virtual MobileOperator* GetRecord(const std::string& a_key , QUERY_REQWEST a_reqType);
   // std::vector<Operator*> GetRecordAll(QUERY_REQWEST a_reqType);   

private:
    OperatorAggregator(const OperatorAggregator& a_other);
    OperatorAggregator operator=(const OperatorAggregator& a_other);
    HashMT<Key, MobileOperator ,Functor , MobileOperator>  m_operatorContainer;

};


}// namespace experis

#endif /* _OPERTATOR_AGREGATOR_HPP_ */
