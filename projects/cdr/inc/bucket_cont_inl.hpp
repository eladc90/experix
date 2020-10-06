#ifndef __BUCKET_CON_INL_HPP__
#define __BUCKET_CON_INL_HPP__

#include "bucket_cont.hpp"
#include "bucket.hpp"

template <class KEY, class VAL>
experis::BucketCont<KEY, VAL>::BucketCont(size_t a_maxSize, CompareFunc a_compareFunc)
    : m_container(a_maxSize, experis::Bucket<KEY, VAL>(a_compareFunc))
{
}

template <class KEY, class VAL>
void experis::BucketCont<KEY, VAL>::Add(const KEY& a_key, const VAL& a_val, unsigned int a_index)
{
    m_container.at(a_index).Add(a_key, a_val);
}

template <class KEY, class VAL>
void experis::BucketCont<KEY, VAL>::Remove(const KEY& a_key, unsigned int a_index)
{
    m_container.at(a_index).Remove(a_key);
}

template <class KEY, class VAL>
size_t experis::BucketCont<KEY, VAL>::Size()const
{
    unsigned long countEle = 0;
    for(unsigned long i = 0; i < m_container.size(); ++i)
    {
        countEle += m_container.at(i).Size();
    }
    return countEle;
}

template <class KEY, class VAL>
typename experis::BucketContItr<KEY, VAL> experis::BucketCont<KEY, VAL>::Find(const KEY& a_key, unsigned int a_index)
{
    try
    {
        typename experis::BucketItr<KEY, VAL> bucketItr = m_container.at(a_index).Find(a_key);

        if(bucketItr != m_container.at(a_index).End())
        {
            return BucketContItr<KEY, VAL>(m_container, bucketItr, a_index);
        }
        return End();
    }

    catch(const std::out_of_range& a_exception)
    {
       return End();
    }
}

template <class KEY, class VAL>
typename experis::BucketContConstItr<KEY, VAL> experis::BucketCont<KEY, VAL>::Find(const KEY& a_key, unsigned int a_index) const {
    try {
        typename experis::BucketConstItr<KEY, VAL> bucketConstItr = m_container.at(a_index).Find(a_key);

        if(bucketConstItr != m_container.at(a_index).CEnd()) {
            return BucketContConstItr<KEY, VAL>(m_container, bucketConstItr, a_index);
        }
        return CEnd();
    }

    catch(const std::out_of_range& a_exception) {
       return CEnd();
    }
}

template <class KEY, class VAL>
typename experis::BucketContItr<KEY, VAL> experis::BucketCont<KEY, VAL>::Begin()
{
    for(unsigned long i = 0; i <= m_container.size() - 1; ++i)
    {
        if(m_container.at(i).Begin() != m_container.at(i).End())
        {
            return BucketContItr<KEY, VAL>(m_container, m_container.at(i).Begin(), i);
        }
    }
    return End();
}

template <class KEY, class VAL>
typename experis::BucketContItr<KEY, VAL> experis::BucketCont<KEY, VAL>::End() {
    unsigned int lastIndex = m_container.size() - 1;
    return BucketContItr<KEY, VAL>(m_container, m_container.at(lastIndex).End(), lastIndex);
}

template <class KEY, class VAL>
typename experis::BucketContConstItr<KEY, VAL> experis::BucketCont<KEY, VAL>::CBegin() const {
    for(unsigned long i = 0; i <= m_container.size() - 1; ++i)
    {
        if(m_container.at(i).Begin() != m_container.at(i).End())
        {
            return BucketContConstItr<KEY, VAL>(m_container, m_container.at(i).CBegin(), i);
        }
    }
    return CEnd(); 
}

template <class KEY, class VAL>
typename experis::BucketContConstItr<KEY, VAL> experis::BucketCont<KEY, VAL>::CEnd() const {
    unsigned int lastIndex = m_container.size() - 1;
    return BucketContConstItr<KEY, VAL>(m_container, m_container.at(lastIndex).CEnd(), lastIndex);
}

#endif//__BUCKET_CON_INL_HPP__
