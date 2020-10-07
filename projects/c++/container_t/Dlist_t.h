#ifndef __DLIST_T_H__
#define __DLIST_T_H__
#include <cstddef> // size_t 
#include "container_t.h"

using namespace std;

template<class T>
class Dlist_t : container_t<T>
{
    public:

        Dlist_t();
        Dlist_t(Dlist_t& _Dlist){}
        ~Dlist_t();
        virtual Dlist_t& operator=(const Dlist_t& _Dlist);
        virtual void Append(const T _element, size_t _index)const;
        virtual void Prepend(const T _element, size_t _index)const;   
        virtual bool Contains(const T _element)const;
        virtual const T& Find(const T& _element)const;
        virtual size_t Count()const{return m_size;}
        virtual size_t Index(const T& _element)const;
        virtual void Insert(const T& _element);
        virtual bool IsEmpty()const;
        virtual void Remove(const T& _element);
        virtual void RemoveAll();
        virtual void RemoveAndDelete(const T& _element);
        virtual void RemoveAndDeleteAll();

    private:


    class Node_t
    {
        public:
                
            Node_t();
            ~Node_t();

            T* m_data;
            Node_t* m_next;
            Node_t* m_prev;
    };

        Node_t m_head;
        Node_t m_tail;
        size_t m_size;
        void AddInIndex(const T _element, size_t _index, Node_t& _head);
        Node_t CheckInList(const T& _element);

};

template<class T>
Dlist_t<T>& Dlist_t<T>::operator=(const Dlist_t& _Dlist)
{
    if (this != _Dlist)
    {
        delete[] m_head;
        delete[] m_tail;
        m_head = _Dlist.m_head;
        m_tail = _Dlist.m_tail;
    }
}

template<class T>
void Dlist_t<T>::Remove(const T& _element)
{
    Node_t* node;
    Node_t* temp = 0;
    try
    {
        node = CheckInList(_element);
    }
    catch(int i)
    {
        return;
    }
    temp = node.GetPrev();
    temp.SetNext(node.GetNext());
    temp = node.GetNext();
    temp.SetPrev(node.GetPrev());
}


template<class T>
void Dlist_t<T>::RemoveAll()
{
    m_head.SetNext(m_tail);
    m_tail.SetPrev(m_head);
}


template<class T>
void Dlist_t<T>::RemoveAndDelete(const T& _element)
{
    Node_t* node;
    try
    {
        node = CheckInList(_element);
    }
    catch(int i)
    {
        return;
    }
    Remove(_element);
    delete[] node;
}



template<class T>
bool Dlist_t<T>::IsEmpty()const
{
    if (!m_size)
    {
        return true;
    }
    return false;
}



template<class T>
void Dlist_t<T>::Insert(const T& _element)
{
    Node_t newNode = new Node_t();
    Node_t* prev = m_tail.GetPrev();
    newNode.SetData(_element);
    newNode.SetNext(m_tail);
    m_tail.SetPrev(newNode);
    prev -> SetNext(newNode);
    m_size++;

}


template<class T>
Dlist_t<T>::Dlist_t()
{
	m_head = new Node_t();
    m_tail = new Node_t();
    m_size = 0;

}


template<class T>
Dlist_t<T>::~Dlist_t()
{
	delete[] m_head;
    delete[] m_tail;
}

template<class T>
void Dlist_t<T>:: Append(const T _element, size_t _index)const
{
    AddInIndex(_element, _index + 1, m_head);
}


template<class T>
void Dlist_t<T>::Prepend(const T _element, size_t _index)const
{
    AddInIndex( _element,  _index - 1, m_head);
}


template<class T>
bool Dlist_t<T>::Contains(const T _element)const
{
    try
    {
        CheckInList(_element);
    }
    catch(int i)
    {
        return false;
    }
    return true;
}




template<class T>
const T& Dlist_t<T>::Find(const T& _element)const
{
    Node_t* node;
    try
    {
        node = CheckInList(_element);
        return node.GetData();
    }
    catch(int i)
    {
        return false;
    }
    return true;
}


template<class T>
void Dlist_t<T>::AddInIndex(const T _element, size_t _index, Node_t& _head)
{
    int i = 0;
    Node_t NewNode = new Node_t();
    Node_t* temp = _head.GetNext();

    if(_index > m_size)
    {
        throw; //TODO;
    }

    m_size++;

    for (; i < _index; _index++)
    {
        temp = temp -> GetNext();
    }

    NewNode.SetNext(temp);
    NewNode.SetPrev(temp -> GetPrev());
    temp -> SetPrev(NewNode);
    temp = temp -> GetPrev();
    temp -> SetNext(NewNode);
    NewNode.SetData(_element);
}



template<class T>
size_t Dlist_t<T>::Index(const T& _element)const
{
    size_t i = m_size;
    Node_t* temp = m_head.GetNext();
    while(i)
    {
        if (temp -> GetData() == _element)
        {
            return i;
        }

        temp = temp -> GetNext();
        i--;
    }
    return 0;
}

template<class T>
Node_t<T> Dlist_t<T>::CheckInList(const T& _element)
{
    size_t i = m_size;
    Node_t* temp = m_head.GetNext();
    while(i)
    {
        if (temp -> GetData() == _element)
        {
            return temp;
        }

        temp = temp -> GetNext();
        i--;
    }
    throw 0;
}



#endif //__DLIST_T_H__