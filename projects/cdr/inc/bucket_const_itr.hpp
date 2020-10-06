#ifndef __BUCKET_CONST_ITR_HPP__
#define __BUCKET_CONST_ITR_HPP__

namespace experis {

template <class KEY, class VAL>
class Bucket;

template <class KEY, class VAL>
class BucketConstItr {
    friend class Bucket<KEY, VAL>;
    typedef typename std::vector<std::pair<KEY, VAL> >::const_iterator CItr;

public:
    //~BucketConstItr() = default
    //BucketConstItr(const BucketConstItr& a_other) = default
    //BucketConstItr& operator=(const BucketConstItr& a_other) = default
    BucketConstItr& operator++() { ++m_constBucketItr; return *this; }
    bool operator==(const BucketConstItr& a_other) const { return m_constBucketItr == a_other.m_constBucketItr; }
    bool operator!= (const BucketConstItr& a_other) const { return m_constBucketItr != a_other.m_constBucketItr; }
    const std::pair<KEY, VAL>& operator*() const { return *m_constBucketItr; }

private:
    BucketConstItr(CItr a_bucketConstItr)
    : m_constBucketItr(a_bucketConstItr) {
    }

    CItr m_constBucketItr;
};

} //experis

#endif //__BUCKET_CONST_ITR_HPP__