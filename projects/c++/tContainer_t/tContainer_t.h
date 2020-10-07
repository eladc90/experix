#ifndef __TCONTAINER_T_H__
#define __TCONTAINER_T_H__

#include <list>
#include <vector>
#include <iostream> 
#include <algorithm>

using namespace std;


template <class T, class CONT>
class tContainer_t
{
    public:

        tContainer_t(){}
        ~tContainer_t(){}
        bool IsEmpty()const{return m_container.empty();}
        size_t Size()const{return m_container.size();}
        const T* FindIf(const T& _element)const;
        const T* FirstElement()const{return m_container.front();}
        const T* LastElement()const{return m_container.back();}
        void Insert(T* _element){m_container.push_back(_element);}
        const T* RemoveByElement(const T& _element);
        void RemoveAllElements(){m_container.clear();}
        void DeleteByElement(const T& _element);
        void DeleteAllElements(){for_each(m_container.begin(), m_container.end(), DeleteByElement);}
        const T* operator[](size_t _index)const;

    private:

        CONT m_container;
        tContainer_t(const tContainer_t& _Container);
        tContainer_t& operator=(const tContainer_t& _Container);

        typedef typename CONT::iterator iter_t;
        typedef typename CONT::const_iterator CIter_t;


    class FindByVal
    {
    public:

        FindByVal(T val): val2find(val){;}
        bool operator()(T comparWith)const {return comparWith == val2find;}
        ~FindByVal(){}

    private:

        T val2find;
    };
};







template <class T, class CONT>
const T* tContainer_t<T, CONT>::RemoveByElement(const T& _element)
{
    CIter_t itr = find_if(m_container.begin(),m_container.end(), FindByVal(_element));
    if (itr == m_container.end())
    {
        return 0;
    }
    T* returnElement= *itr;
    itr = m_container.erase(itr);
    return returnElement;
}


template <class T, class CONT>
const T* tContainer_t<T, CONT>::FindIf(const T& _element)const
{
    CIter_t itr = find_if(m_container.begin(),m_container.end(), FindByVal(_element));
    if (itr == m_container.end())
    {
        return 0;
    }
    return *itr;
}



template <class T, class CONT>
void tContainer_t<T, CONT>::DeleteByElement(const T& _element)
{
    CIter_t itr = find_if(m_container.begin(),m_container.end(), FindByVal(_element));
    if (itr == m_container.end())
    {
        return;
    }
    m_container.erase(itr);
    delete *itr;

}


template <class T, class CONT>
const T* tContainer_t<T, CONT>::operator[](size_t _index)const
{
    iter_t itr = m_container.begin();
    if (_index > m_container.size())
    {
        throw "Invalid INDEX!!";
    }
    if (typeid(this) == typeid(vector <T>))
    {
        return *m_container[_index];
    } 
    for (; _index != 0; itr++ , _index--) {}
    return *itr;
}









#endif //__TCONTAINER_T_H__