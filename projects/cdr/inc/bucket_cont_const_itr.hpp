#ifndef __BUCKET_CONT_CONST_ITR_HPP__
#define __BUCKET_CONT_CONST_ITR_HPP__

#include "bucket_const_itr.hpp"

namespace experis {

template <class KEY, class VAL>
class BucketCont;

template <class KEY, class VAL>
class BucketContConstItr {
    friend class BucketCont<KEY, VAL>;
    typedef typename std::vector<Bucket<KEY, VAL>  > Container;

public:
    ~BucketContConstItr();
    //BucketContConstItr(const BucketContConstItr& a_other) = default
    //BucketContConstItr& operator=(const BucketContConstItr& a_other) = default
    BucketContConstItr& operator++();
    bool operator==(const BucketContConstItr& a_other) const { return m_bucketConstItr == a_other.m_bucketConstItr; }
    bool operator!= (const BucketContConstItr& a_other) const { return m_bucketConstItr != a_other.m_bucketConstItr; }
    const std::pair<KEY, VAL>& operator*() const { return *m_bucketConstItr; }

private:
    BucketContConstItr(const Container& a_container, BucketConstItr<KEY, VAL> a_bucketItr, size_t a_index);

    const Container& m_refContainer;
    BucketConstItr<KEY, VAL> m_bucketConstItr;
    size_t m_contIndex;
};

#include "bucket_cont_const_itr_inl.hpp"

} //experis

#endif //__BUCKET_CONT_CONST_ITR_HPP__