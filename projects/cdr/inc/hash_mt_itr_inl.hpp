#ifndef __HASH_MT_ITR_INL_HPP__
#define __HASH_MT_ITR_INL_HPP__

template<class KEY, class VAL, class HASHFUNC, class UPDATEFUNC>
HashMtItr<KEY, VAL, HASHFUNC, UPDATEFUNC>::HashMtItr(constItr a_hashItr)
: m_cHashItr(a_hashItr) {
}

template<class KEY, class VAL, class HASHFUNC, class UPDATEFUNC>
HashMtItr<KEY, VAL, HASHFUNC, UPDATEFUNC>& HashMtItr<KEY, VAL, HASHFUNC, UPDATEFUNC>::operator++() {
    ++m_cHashItr;
    return *this;
}

#endif //__HASH_MT_ITR_INL_HPP__