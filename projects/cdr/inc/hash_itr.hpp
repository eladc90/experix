#ifndef __HASH_ITR_HPP__
#define __HASH_ITR_HPP__

#include "bucket_cont_itr.hpp"

namespace experis
{
template <class KEY, class VAL, class HASHFUNC>
class Hash;

template <class KEY, class VAL, class HASHFUNC>
class HashItr
{
    friend class Hash<KEY, VAL, HASHFUNC>;
public:
    //~HashItr() = default
    //HashItr(const HashItr& a_other) = default
    //HashItr& operator=(const HashItr& a_other) = default
    HashItr& operator++() { ++m_bucketContItr; return *this; }
    bool operator==(const HashItr& a_other) const { return m_bucketContItr == a_other.m_bucketContItr; }
    bool operator!= (const HashItr& a_other) const { return m_bucketContItr != a_other.m_bucketContItr; }
    VAL& operator*(){ return (*m_bucketContItr).second; }

private:
    HashItr(BucketContItr<KEY,VAL> a_bucketContItr)
    : m_bucketContItr(a_bucketContItr) {
    }

    BucketContItr<KEY,VAL> m_bucketContItr;
};

}//experis

#endif//__HASH_ITR_HPP__
