#ifndef __BUCKET_ITR_HPP__
#define __BUCKET_ITR_HPP__

#include <vector>
#include "bucket.hpp"

namespace experis {

template <class KEY, class VAL>
class Bucket;

template <class KEY, class VAL>
class BucketItr {
    friend class Bucket<KEY, VAL>;
    typedef typename std::vector<std::pair<KEY, VAL> >::iterator Itr;

public:
    //~BucketItr() = default
    //BucketItr(const BucketItr& a_other) = default
    //BucketItr& operator=(const BucketItr& a_other) = default
    BucketItr& operator++() { ++m_bucketItr; return *this; }
    bool operator==(const BucketItr& a_other) const { return m_bucketItr == a_other.m_bucketItr; }
    bool operator!= (const BucketItr& a_other) const { return m_bucketItr != a_other.m_bucketItr; }
    std::pair<KEY, VAL>& operator*() { return *m_bucketItr; }

private:
    BucketItr(Itr a_bucketItr)
    : m_bucketItr(a_bucketItr) {
    }

    Itr m_bucketItr;
};

}//experis

#endif//__BUCKET_ITR_HPP__
