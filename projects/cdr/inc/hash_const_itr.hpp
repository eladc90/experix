#ifndef __HASH_CONST_ITR_HPP__
#define __HASH_CONST_ITR_HPP__

#include "bucket_cont_const_itr.hpp"

namespace experis {

template <class KEY, class VAL, class HASHFUNC>
class Hash;

template <class KEY, class VAL, class HASHFUNC>
class HashConstItr {
    friend class Hash<KEY, VAL, HASHFUNC>;
public:
    //~HashConstItr() = default
    //HashConstItr(const HashConstItr& a_other) = default
    //HashConstItr& operator=(const HashConstItr& a_other) = default
    HashConstItr& operator++() { ++m_bucketContConstItr; return *this; }
    bool operator==(const HashConstItr& a_other) const { return m_bucketContConstItr == a_other.m_bucketContConstItr; }
    bool operator!= (const HashConstItr& a_other) const { return m_bucketContConstItr != a_other.m_bucketContConstItr; }
    const VAL& operator*() const { return (*m_bucketContConstItr).second; }

private:
    HashConstItr(BucketContConstItr<KEY,VAL> a_bucketContConstItr)
    : m_bucketContConstItr(a_bucketContConstItr) {
    }

    BucketContConstItr<KEY,VAL> m_bucketContConstItr;
};

}

#endif //__HASH_CONST_ITR_HPP__