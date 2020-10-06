#ifndef __HASH_MT_ITR_HPP__
#define __HASH_MT_ITR_HPP__

#include "hash_const_itr.hpp"

namespace experis {

template<class KEY, class VAL, class HASHFUNC, class UPDATEFUNC>
class HashMT;

template<class KEY, class VAL, class HASHFUNC, class UPDATEFUNC>
class HashMtItr {
    friend class HashMT<KEY, VAL, HASHFUNC, UPDATEFUNC>;
    typedef HashConstItr<KEY, VAL, HASHFUNC> constItr;
public:
    //~HashItr() = default
    //HashItr(const HashItr& a_other) = default
    //HashItr& operator=(const HashItr& a_other) = default

    HashMtItr& operator++();
    bool operator==(const HashMtItr& a_other) const { return m_cHashItr == a_other.m_cHashItr; }
    bool operator!=(const HashMtItr& a_other) const { return !(*this == a_other); }
    const VAL& operator*() const { return *m_cHashItr; }

private:
    HashMtItr(constItr a_hashItr);

    constItr m_cHashItr;
};

#include "hash_mt_itr_inl.hpp"

} //experis

#endif //__HASH_MT_ITR_HPP__