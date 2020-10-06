#ifndef __HASH_MT_HPP__
#define __HASH_MT_HPP__


#include "mutex.hpp"
#include "hash.hpp"
#include "hash_itr.hpp"
#include "hash_mt_itr.hpp"
#include <string>
#include <iostream>
#include <vector>

namespace experis {


template<class KEY, class VAL, class HASHFUNC, class UPDATEFUNC>
class HashMT {

public:
    typedef bool (*CompareKey)(const KEY& a_firstKey, const KEY& a_secondKey);

    HashMT(size_t a_size, HASHFUNC a_hashFunc, CompareKey a_compare);
    ~HashMT() throw();
    const VAL& Get(const KEY& a_key);
    void Update(const KEY& a_key, UPDATEFUNC a_update); 

private:
    HashMT(const HashMT& a_other); 
    HashMT& operator=(const HashMT& a_other); 
    void Add(const KEY& a_key, const VAL& a_val); 

private:
    Hash<KEY, VAL, HASHFUNC> m_hash;
    std::vector<Mutex>  m_lockes;
    HASHFUNC m_hashFunc;
    size_t m_size;
   // bool m_woekMode;
};

#include "hash_mt_inl.hpp"

}

#endif //__HASH_MT_HPP__
