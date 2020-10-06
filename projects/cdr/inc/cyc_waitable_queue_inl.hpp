#include <exception>
#include <iostream>
#include <string>

template<typename ValType>
WaitableQueue<ValType>::WaitableQueue(size_t a_capacity)
: m_mutex()
, m_isDestroyed(false)
, m_capacity(a_capacity)
, m_waitingsNumber(0)
, m_condVar()
, m_queue()
{
}

template<typename ValType>
WaitableQueue<ValType>::~WaitableQueue(){

    m_mutex.Lock();
    m_isDestroyed=true;
    m_mutex.UnLock();

    if(m_waitingsNumber>0){
        m_condVar.Broadcast();
        m_condVar.Wait(&m_mutex);
    }
}

template<typename ValType>
bool WaitableQueue<ValType>::IsEmpty()const{

    return m_queue.empty();
} 

template<typename ValType>
size_t WaitableQueue<ValType>::Size()const{

    return m_queue.size();
}

template<typename ValType>
void WaitableQueue<ValType>::Enqueue(ValType a_value){
 
 	m_mutex.Lock();

    while(m_queue.size()>=m_capacity &&(!m_isDestroyed))   //capacity is even to queue num of element and not destroyed 
    {
        ++m_waitingsNumber;
        m_condVar.Wait(&m_mutex);                                //wait for dequeue element 
        --m_waitingsNumber;
    }

    if(m_isDestroyed){

        if(m_waitingsNumber==0){
            m_condVar.Signal();
        }
        m_mutex.UnLock();
        throw std::runtime_error("Enqueue whaen destroyed");
    }  

    m_queue.push(a_value);

    m_mutex.UnLock();
    m_condVar.Signal(); 
}

template<typename ValType>
void WaitableQueue<ValType>::Dequeue(ValType* a_value){

 	m_mutex.Lock();

    while(m_queue.empty() && (!m_isDestroyed)){
        ++m_waitingsNumber;
        m_condVar.Wait(&m_mutex);
        --m_waitingsNumber;
    }
    if(m_isDestroyed){
        if(m_waitingsNumber==0){

            m_condVar.Signal();
        }
        m_mutex.UnLock();
        throw std::runtime_error("Dequeue after des");
    }
    else{

        (*a_value) = m_queue.front();

        m_queue.pop();

		#ifdef DEBUG 
 	       /*  std::cout<<" value - "<<(std::string)(*(a_value[0]))<<" Pulled from queue "<< std::endl; */
    	#endif	
        m_condVar.Signal(); 
        m_mutex.UnLock();
    }          
}





