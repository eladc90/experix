#ifndef __HASH_INL_HPP__
#define __HASH_INL_HPP__

#include <cmath>

#include "hash.hpp"
#include "bucket_cont_itr.hpp"

template<class KEY, class VAL, class HASHFUNC>
experis::Hash<KEY, VAL, HASHFUNC>::Hash(size_t a_size, HASHFUNC a_hashFunc, CompareKey a_compare)
    : BucketCont<KEY, VAL>(closestPrimeNumber(a_size), a_compare)
    , m_hashFunc(a_hashFunc)
    , m_size(closestPrimeNumber(a_size)){
}

template <class KEY, class VAL, class HASHFUNC>
void experis::Hash<KEY, VAL, HASHFUNC>::Add(const KEY& a_key, const VAL& a_val) {
    unsigned int indexCont = m_hashFunc(a_key) % m_size;
    BucketContItr<KEY, VAL> itr = BucketCont<KEY, VAL>::Find(a_key, indexCont);
    if(itr != BucketCont<KEY, VAL>::End()) {
        (*itr).second = a_val;
        return;
    }

    BucketCont<KEY, VAL>::Add(a_key, a_val, indexCont);
}

template <class KEY, class VAL, class HASHFUNC>
void  experis::Hash<KEY, VAL, HASHFUNC>::Remove(const KEY& a_key) {
    unsigned int indexCont = m_hashFunc(a_key) % m_size;
    BucketCont<KEY, VAL>::Remove(a_key, indexCont);
}

template <class KEY, class VAL, class HASHFUNC>
experis::HashItr<KEY, VAL, HASHFUNC> experis::Hash<KEY, VAL, HASHFUNC>::Find(const KEY& a_key) {
    unsigned int indexCont = m_hashFunc(a_key) % m_size;
    experis::BucketContItr<KEY, VAL> itr = BucketCont<KEY, VAL>::Find(a_key, indexCont);

    if(itr == BucketCont<KEY, VAL>::End()) {
        return End();
    }

    return HashItr<KEY, VAL, HASHFUNC>(itr);
}

template <class KEY, class VAL, class HASHFUNC>
experis::HashConstItr<KEY, VAL, HASHFUNC> experis::Hash<KEY, VAL, HASHFUNC>::Find(const KEY& a_key) const {
    unsigned int indexCont = m_hashFunc(a_key) % m_size;
    experis::BucketContConstItr<KEY, VAL> itr = BucketCont<KEY, VAL>::Find(a_key, indexCont);

    if(itr == BucketCont<KEY, VAL>::CEnd()) {
        return CEnd();
    }

    return HashConstItr<KEY, VAL, HASHFUNC>(itr);
}

template <class KEY, class VAL, class HASHFUNC>
VAL& experis::Hash<KEY, VAL, HASHFUNC>::Get(const KEY& a_key) {
    unsigned int indexCont = m_hashFunc(a_key) % m_size;

    experis::BucketContItr<KEY, VAL> itr = BucketCont<KEY, VAL>::Find(a_key, indexCont);

    if(itr == BucketCont<KEY, VAL>::End()) {
        throw std::out_of_range("No such key");
    }

    return (*itr).second;
}

template <class KEY, class VAL, class HASHFUNC>
const VAL& experis::Hash<KEY, VAL, HASHFUNC>::Get(const KEY& a_key) const {
    unsigned int indexCont = m_hashFunc(a_key) % m_size;

    experis::BucketContConstItr<KEY, VAL> itr = BucketCont<KEY, VAL>::Find(a_key, indexCont);

    if(itr == BucketCont<KEY, VAL>::CEnd()) {
        throw std::out_of_range("No such key");
    }

    return (*itr).second;
}

template <class KEY, class VAL, class HASHFUNC>
VAL& experis::Hash<KEY, VAL, HASHFUNC>::operator[](const KEY& a_key) {
    return Get(a_key);
}

template <class KEY, class VAL, class HASHFUNC>
const VAL& experis::Hash<KEY, VAL, HASHFUNC>::operator[](const KEY& a_key) const {
    return Get(a_key);
}


template <class KEY, class VAL, class HASHFUNC>
size_t experis::Hash<KEY, VAL, HASHFUNC>::closestPrimeNumber(size_t a_size) {
    while(1)
    {
        if(isPrime(++a_size))
        {
            return a_size;
        }
    }
}

template <class KEY, class VAL, class HASHFUNC>
bool experis::Hash<KEY, VAL, HASHFUNC>::isPrime(size_t a_num) {
    if(a_num % 2 == 0)
    {
        return false;
    }
    for(size_t i = 3; i < sqrt(a_num); i+=2)
    {
        if(a_num % i == 0)
        {
            return false;
        }
    }
    return true;
}


#endif//__HASH_INL_HPP__
