#ifndef __BUCKET_CONT_ITR_INL_HPP__
#define __BUCKET_CONT_ITR_INL_HPP__

#include "bucket_cont.hpp"

template <class KEY, class VAL>
experis::BucketContItr<KEY, VAL>::~BucketContItr() {
}

template <class KEY, class VAL>
typename experis::BucketContItr<KEY, VAL>& experis::BucketContItr<KEY, VAL>::operator++() {
    if(m_bucketItr == m_refContainer.at(m_contIndex).End()) {
        do {
            ++m_contIndex;
        } while(m_refContainer.at(m_contIndex).Begin() == m_refContainer.at(m_contIndex).End());

        m_bucketItr = m_refContainer.at(m_contIndex).Begin();
    }
    else {
        ++m_bucketItr;
    }

    return *this;
}

#endif//__BUCKET_CONT_ITR_INL_HPP__
