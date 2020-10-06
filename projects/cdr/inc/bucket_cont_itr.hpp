#ifndef __BUCKET_CON_ITR_HPP__
#define __BUCKET_CON_ITR_HPP__

#include "bucket.hpp"
#include "bucket_itr.hpp"

namespace experis
{
template <class KEY, class VAL>
class BucketCont;

template <class KEY, class VAL>
class BucketContItr
{
    friend class BucketCont<KEY, VAL>;

public:
    ~BucketContItr();
    //BucketContItr(const BucketItr& a_other) = default
    //BucketContItr& operator=(const BucketItr& a_other) = default
    BucketContItr& operator++();
    bool operator==(const BucketContItr& a_other) const { return m_bucketItr == a_other.m_bucketItr; }
    bool operator!= (const BucketContItr& a_other) const { return m_bucketItr != a_other.m_bucketItr; }
    std::pair<KEY, VAL>& operator*(){ return *m_bucketItr; }

private:
    BucketContItr(std::vector<Bucket<KEY, VAL>  >& a_container, BucketItr<KEY, VAL> a_bucketItr, size_t a_index)
    : m_refContainer(a_container), m_bucketItr(a_bucketItr), m_contIndex(a_index)
    {
    }

    std::vector<Bucket<KEY, VAL> >& m_refContainer;

    BucketItr<KEY, VAL> m_bucketItr;
    size_t m_contIndex;
};
}//experis

#include "bucket_cont_itr_inl.hpp"

#endif//__BUCKET_CON_ITR_HPP__
