#ifndef __ASCIIIO_T_H__
#define __ASCIIIO_T_H__


#include <string>
#include <stdio.h>
#include "virtIO_t.h"

using namespace std;

class asciiIO_t : public virtIO_t
{
    public:

        asciiIO_t(){}
        ~asciiIO_t();
        asciiIO_t(const char* _fileName, const char* _mode);

        virtual void Open(const char* _fileName, const char* _mode); 
        virtual void operator<<(void *_writeBuff);

    private:

        asciiIO_t(const asciiIO_t& x){;}
        virtual asciiIO_t& operator=(const asciiIO_t& _ascii){};

};


asciiIO_t::~asciiIO_t()
{
    Close(m_file);
}

asciiIO_t::asciiIO_t(const char* _fileName, const char* _mode):virtIO_t(_fileName, _mode)
{
    m_file = fopen(_fileName, _mode);
    if (m_file == 0)
    {
        SetStatus(cant_open_file_e);//TODO
    } 
    SetStatus(ok_e);
}


void asciiIO_t::Open(const char* _fileName, const char* _mode)
{
    m_file = fopen(_fileName, _mode);
    if (m_file == 0)
    {
        SetStatus(cant_open_file_e);//TODO
    } 
    SetStatus(ok_e);
}


void asciiIO_t::operator<<(void *_writeBuff)
{
    int status = 0;
    if (GetStatus() != ok_e)
    {
        throw GetStatus(); // TODO
    }
    status = fwrite(_writeBuff, "%d", _intToWrite);
    if (status <= 0)
    {
        throw 0; //TODO
    }
    SetSize(); 
}





#endif //__ASCIIIO_T_H__