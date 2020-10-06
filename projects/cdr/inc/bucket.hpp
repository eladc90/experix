#ifndef __BUCKET_HPP__
#define __BUCKET_HPP__

#include <vector>
#include <cstdlib>
#include <utility>

#include "bucket_itr.hpp"
#include "bucket_const_itr.hpp"

namespace experis {

template <class KEY, class VAL>
class Bucket {
    typedef bool(*CompareFunc)(const KEY& a_firstKey, const KEY& a_secondKey);
    typedef std::pair<KEY, VAL> PAIR;
    typedef typename std::vector<PAIR> BucketType;
    
public:
    Bucket(CompareFunc a_compareFunc);
    //~Bucket() = default
    //Bucket(const Bucket&) = default
    //Bucket& operator=(const Bucket&) = default
    
    void Add(const KEY& a_key, const VAL& a_val);
    void Remove(const KEY& a_key);
    BucketItr<KEY, VAL> Find(const KEY& a_key);
    BucketConstItr<KEY, VAL> Find(const KEY& a_key) const; //If the bucket obj. is const, the function returns a bucket_const_iterator.
                                                          //Otherwise, it returns a bucket_iterator.
    size_t Size()const { return m_bucket.size(); }

    BucketItr<KEY, VAL> Begin();
    BucketItr<KEY, VAL> End();

    BucketConstItr<KEY, VAL> CBegin() const;
    BucketConstItr<KEY, VAL> CEnd() const;

private:
    void RemoveWithCompareFunc(const KEY& a_key);
    void RemoveWithCompareOperator(const KEY& a_key);

    BucketItr<KEY, VAL> FindWithCompareFunc(const KEY& a_key);
    BucketItr<KEY, VAL> FindWithCompareOperator(const KEY& a_key);

    BucketConstItr<KEY, VAL> FindWithCompareFunc(const KEY& a_key) const;
    BucketConstItr<KEY, VAL> FindWithCompareOperator(const KEY& a_key) const;

    CompareFunc m_compareFunc;
    BucketType m_bucket;
};
}//experis

#include "bucket_inl.hpp"

#endif//__BUCKET_HPP__
