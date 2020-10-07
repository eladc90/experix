#ifndef __CONTAINER_T_H__
#define __CONTAINER_T_H__


template<class T>
class container_t
{
    public:

        container_t();
        container_t(const container_t& _container);
        virtual ~container_t();

        virtual container_t& operator=(const container_t& _container){}
        virtual void Append(const T _element, size_t _index)const = 0;
        virtual void Prepend(const T _element, size_t _index)const = 0;   
        virtual bool Contains(const T _element)const = 0;
        virtual size_t Count()const = 0;
        virtual const T& Find(const T& _element)const = 0;
        virtual size_t Index(const T& _element)const = 0;
        virtual void Insert(const T& _element) = 0;
        virtual bool IsEmpty()const = 0;
        virtual void Remove(const T& _element) = 0;
        virtual void RemoveAll() = 0;
        virtual void RemoveAndDelete(const T& _element) = 0;
        virtual void RemoveAndDeleteAll() = 0;

    private:


};


#endif //__CONTAINER_T_H__