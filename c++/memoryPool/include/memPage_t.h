#ifndef __MEMPAGE_T_H__
#define __MEMPAGE_T_H__

#include "memManager_t.h"
#include <iostream> 

using namespace std;

class MemPage_t: public MemManager_t
{
    public:

        MemPage_t();
        MemPage_t(size_t _capacity);
        virtual ~MemPage_t();
        virtual byte Read(const void *_buffer, size_t nBytes);
        virtual byte Read(const void *_buffer, size_t _from, size_t nBytes);
        virtual byte Write(const void *_buffer, size_t nBytes);
        virtual byte Write(const void *_buffer, size_t _from, size_t nBytes);
        size_t GetCapacity()const{return m_capacity;}
        static size_t GetGCapacity(){return mg_defCapacity;}

    private:

        char *m_page;
        size_t m_capacity;
        static size_t mg_defCapacity;
        MemPage_t(const MemPage_t& _page){;}
        MemPage_t& operator=(const MemPage_t& _page){;}
        byte MyRead(void *_buffer, size_t _from, size_t nBytes);
        byte MyWrite(void *_buffer, size_t _from, size_t nBytes);
};

#endif //__MEMPAGE_T_H__