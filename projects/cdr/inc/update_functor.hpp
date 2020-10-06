#ifndef _UPDATEFUNC_HPP_
#define _UPDATEFUNC_HPP_

#include "mobile_operator.hpp"
#include "cdr.hpp"
#include "customer.hpp"


namespace experis
{

class MobileOpUpdate{

public:
    MobileOpUpdate(Cdr* a_cdr):m_cdr(a_cdr){}
   // ~MobileOpUpdate();
    MobileOperator* operator()(MobileOperator* a_mobileOperator){  (*a_mobileOperator) += m_cdr; 

	return a_mobileOperator;
 }


private:
    Cdr* m_cdr; 
};




class CustomerUpdate{

public:
    CustomerUpdate(Cdr* a_cdr):m_cdr(a_cdr){}
   // ~CustomerUpdate();
    Customer* operator()(Customer* a_customer){  (*a_customer) += m_cdr; 
    
	return a_customer;
    }

private:
    Cdr* m_cdr; 
};




} // namespace experis


#endif // _UPDATEFUNC_HPP_
