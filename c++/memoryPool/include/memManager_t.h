#ifndef __MEMMANAGER_T_H__
#define __MEMMANAGER_T_H__
#include <cstdlib>
#include <iostream> 

using namespace std;


typedef unsigned char byte;

class MemManager_t
{
    public:

        virtual ~MemManager_t(){;};
        MemManager_t():m_actualSize(0), m_position(0){}
        bool IsEmpty()const;
        size_t GetPosition()const{return m_position;}
        void SetPosition(size_t _pos);
        const size_t GetActualSize(){return m_actualSize;}

        virtual byte Read(const void *_buffer, size_t nBytes) = 0;
        virtual byte Read(const void *_buffer, size_t _from, size_t nBytes)= 0;
        virtual byte Write(const void *_buffer, size_t nBytes)= 0;
        virtual byte Write(const void *_buffer, size_t _from, size_t nBytes) = 0;

    protected:

        void SetActualSize(size_t _actualSize);

    private:

        size_t m_position;
        size_t m_actualSize;

        MemManager_t(MemManager_t& _mm){;}
        MemManager_t& operator=(MemManager_t& _mm){;}
};





#endif //__MEMMANAGER_T_H__