#ifndef __HASH_HPP__
#define __HASH_HPP__

#include <utility>

#include "bucket_cont.hpp"
#include "hash_itr.hpp"
#include "hash_const_itr.hpp"

namespace experis {

template<class KEY, class VAL, class HASHFUNC>
class Hash : BucketCont<KEY, VAL> {
    typedef bool (*CompareKey)(const KEY& a_firstKey, const KEY& a_secondKey);

public:
    Hash(size_t a_size, HASHFUNC a_hashFunc, CompareKey a_compare); //throws bad_alloc on memory allocation fail
    //~Hash() = default
    //Hash(const Hash& a_other) = default
    //Hash& operator=(const Hash& a_other) = default

    void Add(const KEY& a_key, const VAL& a_val); //throws bad_alloc if allocation failed
    void Remove(const KEY& a_key); //throws out_of_range when no such key is found

    VAL& Get(const KEY& a_key); //throws out_of_range when no such key is found
    const VAL& Get(const KEY& a_key) const; //throws out_of_range when no such key is found

    HashItr<KEY, VAL, HASHFUNC> Find(const KEY& a_key);
    HashConstItr<KEY, VAL, HASHFUNC> Find(const KEY& a_key) const; //If the hash obj. is const, the function returns a hash_cont_itr.
                                                                   //Otherwise, it returns a hash_itr.
                                                                
    VAL& operator[](const KEY& a_key); //throws out_of_range when no such key is found
    const VAL& operator[](const KEY& a_key) const; //throws out_of_range when no such key is found

    size_t Size()const { return BucketCont<KEY, VAL>::Size(); }

    HashItr<KEY, VAL, HASHFUNC> Begin() { return HashItr<KEY, VAL, HASHFUNC>(BucketCont<KEY, VAL>::Begin()); }
    HashItr<KEY, VAL, HASHFUNC> End() { return HashItr<KEY, VAL, HASHFUNC>(BucketCont<KEY, VAL>::End()); }

    HashConstItr<KEY, VAL, HASHFUNC> CBegin() const { return HashConstItr<KEY, VAL, HASHFUNC>(BucketCont<KEY, VAL>::CBegin()); }
    HashConstItr<KEY, VAL, HASHFUNC> CEnd() const { return HashConstItr<KEY, VAL, HASHFUNC>(BucketCont<KEY, VAL>::CEnd()); }

private:
    size_t closestPrimeNumber(size_t a_size);
    bool isPrime(size_t a_num);

    HASHFUNC m_hashFunc;
    size_t m_size;
};

}//experis

#include "hash_inl.hpp"

#endif//__HASH_HPP__
