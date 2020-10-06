#ifndef __BUCKET_CON_HPP__
#define __BUCKET_CON_HPP__

#include <vector>
#include "bucket.hpp"
#include "bucket_cont_itr.hpp"
#include "bucket_cont_const_itr.hpp"

namespace experis {

template <class KEY, class VAL>
class BucketCont
{
    typedef bool(*CompareFunc)(const KEY& a_firstKey, const KEY& a_secondKey);
    typedef typename std::vector<Bucket<KEY, VAL> > ContType;

public:
    BucketCont(size_t a_maxSize, CompareFunc a_compareFunc);
    //~BucketCont()
    //BucketCont(const BucketCont&) = default
    //BucketCont& operator=(const BucketCont&)
    void Add(const KEY& a_key, const VAL& a_val, unsigned int a_index);
    void Remove(const KEY& a_key, unsigned int a_index);
    BucketContItr<KEY, VAL> Find(const KEY& a_key, unsigned int a_index);
    BucketContConstItr<KEY, VAL> Find(const KEY& a_key, unsigned int a_index) const;
    size_t Size()const;

    BucketContItr<KEY, VAL> Begin();
    BucketContItr<KEY, VAL> End();

    BucketContConstItr<KEY, VAL> CBegin() const;
    BucketContConstItr<KEY, VAL> CEnd() const;

private:
    ContType m_container;
};

}//experis

#include "bucket_cont_inl.hpp"

#endif//__BUCKET_CON_HPP__
