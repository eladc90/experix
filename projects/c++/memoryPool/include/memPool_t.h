#ifndef __MEMPOOL_T_H__
#define __MEMPOOL_T_H__
#include "memPage_t.h"
#include <vector>

using namespace std;


class memPool_t : public MemManager_t
{
    public:

        memPool_t();
        memPool_t(size_t _capacity);
        virtual ~memPool_t();
        virtual byte Read(const void *_buffer, size_t nBytes);
        virtual byte Read(const void *_buffer, size_t _from, size_t nBytes);
        virtual byte Write(const void *_buffer, size_t nBytes);
        virtual byte Write(const void *_buffer, size_t _from, size_t nBytes);
        size_t GetPoolCapacity()const{return m_pageCapacity * m_pool.size();}

    private:

        vector <MemPage_t *> m_pool;
        static size_t mg_defeltCapacity;
        size_t m_pageCapacity;

        memPool_t(const memPool_t& _pool){}
        memPool_t& operator=(memPool_t& _pool){}
        byte MyRead(void *_buffer, size_t _from, size_t nBytes);
        byte MyWrite(void *_buffer, size_t _from, size_t nBytes);


};




#endif //__MEMPOOL_T_H__