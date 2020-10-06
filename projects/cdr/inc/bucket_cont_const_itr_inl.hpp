#ifndef __BUCKET_CONT_CONST_ITR_INL_HPP__
#define __BUCKET_CONT_CONST_ITR_INL_HPP__

template <class KEY, class VAL>
BucketContConstItr<KEY,VAL>::BucketContConstItr(const Container& a_container, BucketConstItr<KEY, VAL> a_bucketConstItr, size_t a_index)
: m_refContainer(a_container)
, m_bucketConstItr(a_bucketConstItr)
, m_contIndex(a_index) {
}

template <class KEY, class VAL>
BucketContConstItr<KEY, VAL>::~BucketContConstItr() {
}

template <class KEY, class VAL>
BucketContConstItr<KEY, VAL>& BucketContConstItr<KEY, VAL>::operator++() {
     ++m_bucketConstItr;
    if(m_bucketConstItr == m_refContainer.at(m_contIndex).CEnd()) {
        do {
            ++m_contIndex;
        } while(m_refContainer.at(m_contIndex).CBegin() == m_refContainer.at(m_contIndex).CEnd() && m_contIndex != m_refContainer.size() - 1);

        m_bucketConstItr = m_refContainer.at(m_contIndex).CBegin();
    }

    return *this;
}

#endif //__BUCKET_CONT_CONST_ITR_INL_HPP__