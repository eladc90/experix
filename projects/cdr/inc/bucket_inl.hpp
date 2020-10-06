#ifndef __BUCKET_INL_HPP__
#define __BUCKET_INL_HPP__

#include "bucket.hpp"
#include <stdexcept>

template <class KEY, class VAL>
experis::Bucket<KEY, VAL>::Bucket(CompareFunc a_compareFunc)
    : m_compareFunc(a_compareFunc), m_bucket() {
}

template <class KEY, class VAL>
void experis::Bucket<KEY, VAL>::Add(const KEY& a_key, const VAL& a_val) {
    m_bucket.push_back(std::pair<KEY, VAL>(a_key, a_val));
}

template <class KEY, class VAL>
void experis::Bucket<KEY, VAL>::Remove(const KEY& a_key) {
    if(m_compareFunc) {
        RemoveWithCompareFunc(a_key);
    }
    else {
        RemoveWithCompareOperator(a_key);
    }
}

template <class KEY, class VAL>
experis::BucketItr<KEY, VAL> experis::Bucket<KEY, VAL>::Find(const KEY& a_key) {
    return (m_compareFunc) ? FindWithCompareFunc(a_key) : FindWithCompareOperator(a_key);
}

template <class KEY, class VAL>
experis::BucketConstItr<KEY, VAL> experis::Bucket<KEY, VAL>::Find(const KEY& a_key) const {
    return (m_compareFunc) ? FindWithCompareFunc(a_key) : FindWithCompareOperator(a_key);
}

template <class KEY, class VAL>
void experis::Bucket<KEY, VAL>::RemoveWithCompareFunc(const KEY& a_key) {
    for(typename BucketType::iterator i = m_bucket.begin(); i != m_bucket.end(); ++i) {
        if(m_compareFunc(a_key, (*i).first)) {
            m_bucket.erase(i);
            return;
        }
    }
    throw std::out_of_range("No such value found");
}

template <class KEY, class VAL>
void experis::Bucket<KEY, VAL>::RemoveWithCompareOperator(const KEY& a_key) {
    for(typename BucketType::iterator i = m_bucket.begin(); i != m_bucket.end(); ++i) {
        if(a_key == (*i).first) {
            m_bucket.erase(i);
            return;
        }
    }
    throw std::out_of_range("No such value found");
}

template <class KEY, class VAL>
typename experis::BucketItr<KEY, VAL> experis::Bucket<KEY, VAL>::FindWithCompareFunc(const KEY& a_key) {
    for(experis::BucketItr<KEY, VAL> i = Begin(); i != End(); ++i) {
        if(m_compareFunc(a_key, (*i).first)) {
            return i;
        }
    }
    return End();
}

template <class KEY, class VAL>
typename experis::BucketItr<KEY, VAL> experis::Bucket<KEY, VAL>::FindWithCompareOperator(const KEY& a_key) {
    for(experis::BucketItr<KEY, VAL> i = Begin(); i != End(); ++i) {
        if(a_key == (*i).first) {
            return i;
        }
    }
    return End();
}

template <class KEY, class VAL>
typename experis::BucketConstItr<KEY, VAL> experis::Bucket<KEY, VAL>::FindWithCompareFunc(const KEY& a_key) const {
    for(experis::BucketConstItr<KEY, VAL> i = CBegin(); i != CEnd(); ++i) {
        if(m_compareFunc(a_key, (*i).first)) {
            return i;
        }
    }
    return CEnd();
}

template <class KEY, class VAL>
typename experis::BucketConstItr<KEY, VAL> experis::Bucket<KEY, VAL>::FindWithCompareOperator(const KEY& a_key) const {
    for(experis::BucketConstItr<KEY, VAL> i = CBegin(); i != CEnd(); ++i) {
        if(a_key == (*i).first) {
            return i;
        }
    }
    return CEnd();
}

template <class KEY, class VAL>
typename experis::BucketItr<KEY, VAL> experis::Bucket<KEY, VAL>::Begin() {
    return BucketItr<KEY, VAL>(m_bucket.begin());
}

template <class KEY, class VAL>
typename experis::BucketItr<KEY, VAL> experis::Bucket<KEY, VAL>::End() {
    return BucketItr<KEY, VAL>(m_bucket.end());
}

template <class KEY, class VAL>
typename experis::BucketConstItr<KEY, VAL> experis::Bucket<KEY, VAL>::CBegin() const {
    return BucketConstItr<KEY, VAL>(m_bucket.begin());
}

template <class KEY, class VAL>
typename experis::BucketConstItr<KEY, VAL> experis::Bucket<KEY, VAL>::CEnd() const {
    return BucketConstItr<KEY, VAL>(m_bucket.end());
}

#endif//__BUCKET_INL_HPP__
