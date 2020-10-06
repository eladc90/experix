#ifndef __VECTOR_T_H__
#define __VECTOR_T_H__


#include "container_t.h"

template<class T>
class vector_t : public container_t<T>
{
    public:
        vector_t();
        vector_t(const vector_t& _vec);
        ~vector_t();
        virtual vector_t& operator=(const vector_t& _vec);
        virtual void Append(const T* _element, size_t _index)const;
        virtual void Prepend(const T _element, size_t _index)const;   
        virtual bool Contains(const T _element)const;
        virtual size_t Count()const;
        virtual const T& Find(const T& _element)const;
        virtual size_t Index(const T& _element)const;
        virtual void Insert(const T& _element);
        virtual bool IsEmpty()const;
        virtual void Remove(const T& _element);
        virtual void RemoveAll();
        virtual void RemoveAndDelete(const T& _element);
        virtual void RemoveAndDeleteAll();

    private:

        T** m_vector; 
        size_t m_size;
        size_t m_capacity;

};


template <class T>
Vector_t<T>::Vector_t () :m_size(0), m_capacity(16)
{
    m_vector = new T*[m_capacity];
}



template <class T>
Vector_t<T>::Vector_t (const Vector_t& _vec) : m_size(_vec.m_size), m_capacity(_vec.m_capacity)
{
    m_vector = new T*[m_capacity];
    size_t i = 0;
    for (; i < _vec.m_size; i++)
    {
        m_elems[i] = _vec.m_elems[i];
    }
}


template <class T>
Vector_t<T>::~Vector_t ()
{
	m_size = 0; 
    delete[] m_vector;
}




template <class T>
Container_t<T>& Vector_t<T>::Append (const T* _element, size_t _index)
{
    size_t i = _index + 1;
    if (!_elem)
    {
        throw TException_t<int>(0, __FILE__, __LINE__, "error: can't append to vector");
    }
    if (_index > m_size)
    {
        throw TException_t<int>(-1, __FILE__, __LINE__, "error: Index out of bounds");
    }

    for (; i < m_size - 1; i++)
    {
        m_vector[i+1] = m_vector[i];
    }

    m_vector[_index] = (T*)_elem;

    m_size++;
    return *this;
}











#endif //__VECTOR_T_H__