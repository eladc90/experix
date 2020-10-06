#ifndef __BINIO_T_H__
#define __BINIO_T_H__



#include <string>
#include <stdio.h>
#include "virtIO_t.h"

using namespace std;

class binIO_t : public virtIO_t
{
    public:

        binIO_t(){}
        ~binIO_t(){close(m_file);}
        binIO_t(const char* _fileName, const char* _mode);

        virtual void Open(const char* _fileName, const char* _mode);
        virtual void operator<<(int _intToWrite);
    
    private:

        binIO_t(const binIO_t& ){}
        virtual binIO_t& operator=(const binIO_t% _binIO){} 


};


binIO_t::binIO_t(const char* _fileName, const char* _mode)
{
    m_file = fopen(_fileName, _mode)
    if(m_file == 0)
    {
        SetStatus(cant_open_file_e);
        throw 0;//TODO
    }
    SetStatus(ok_e);
}


void binIO_t::Open(const char* _fileName, const char* _mode)
{
    if (GetStatus() != ok_e)
    {
        throw 0; //TODO
    }
    m_file = fopen(_fileName, _mode);
    if (m_file == 0)
    {
        SetStatus(cant_open_file_e);//TODO
        throw 0;//TODO
    } 
    SetStatus(ok_e);
}


void binIO_t::operator<<(int _intToWrite)
{
    int status = 0;
    if (GetStatus() != ok_e)
    {
        throw GetStatus(); // TODO
    }
    status = fwrite(m_file, "%d", _intToWrite);
    if (status < 0)
    {
        throw 0; //TODO
    }
    SetSize(); 
}











#endif //__BINIO_T_H__