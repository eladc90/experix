#ifndef __HASH_MT_INL_HPP__
#define __HASH_MT_INL_HPP__


static const int lockPerSize =10;

template<class KEY, class VAL, class HASHFUNC, class UPDATEFUNC>
HashMT<KEY, VAL, HASHFUNC, UPDATEFUNC>::HashMT(size_t a_size, HASHFUNC a_hashFunc, CompareKey a_compare)
: m_hash(a_size, a_hashFunc, a_compare)
, m_lockes(a_size/lockPerSize)
, m_hashFunc(a_hashFunc)
, m_size(a_size)
//, m_woekMode(true) 
{
}


template<class KEY, class VAL, class HASHFUNC, class UPDATEFUNC>
HashMT<KEY, VAL, HASHFUNC, UPDATEFUNC>::~HashMT() throw() {

    for(int i=0 ; i< m_lockes.size(); ++i)
    {
        m_lockes[i].Lock();   
    }

   // m_woekMode=false;    

   /*for(int i=0 ; i< m_lockes.size(); ++i)
    {
        m_lockes[i].UnLock();   
    }*/

}


template<class KEY, class VAL, class HASHFUNC, class UPDATEFUNC>
void HashMT<KEY, VAL, HASHFUNC, UPDATEFUNC>::Add(const KEY& a_key, const VAL& a_val) {

    size_t lockIndex= (m_hashFunc(a_key)% m_size ) % m_lockes.size();
    m_lockes[lockIndex].Lock();

    try{ 
            m_hash.Add(a_key, a_val);
            m_lockes[lockIndex].UnLock();

        }
        catch(const std::bad_alloc& a_exception) {
            m_lockes[lockIndex].UnLock();
            throw;
        }

    
}


template<class KEY, class VAL, class HASHFUNC, class UPDATEFUNC>
const VAL& HashMT<KEY, VAL, HASHFUNC, UPDATEFUNC>::Get(const KEY& a_key){

    size_t lockIndex= (m_hashFunc(a_key)% m_size ) % m_lockes.size();
    m_lockes[lockIndex].Lock();

  
        try {
            const VAL& value = m_hash.Get(a_key);
            m_lockes[lockIndex].UnLock();
            return value;
        }
        catch(const std::out_of_range& a_exception) {
            m_lockes[lockIndex].UnLock();
            throw;
        }

    
    
}


template<class KEY, class VAL, class HASHFUNC, class UPDATEFUNC>
void HashMT<KEY, VAL, HASHFUNC, UPDATEFUNC>::Update(const KEY& a_key, UPDATEFUNC a_update) {

    size_t lockIndex= (m_hashFunc(a_key)% m_size ) % m_lockes.size();
    m_lockes[lockIndex].Lock();

        try {

            try{
                    const VAL& val = m_hash.Get(a_key);
                    m_hash.Add(a_key, a_update(val));
                    std::cout<<" & Update info "<<std::endl;	      
                    m_lockes[lockIndex].UnLock();
                }
                catch(const std::out_of_range& a_exception) {
                    m_hash.Add(a_key, a_update);
                    std::cout<<" & Add to new "<<std::endl;	      
                    m_lockes[lockIndex].UnLock();
                }
        }
        catch(const std::bad_alloc& a_exception) {

                m_lockes[lockIndex].UnLock();
                throw;
            }
    }





#endif //__HASH_MT_INL_HPP__
