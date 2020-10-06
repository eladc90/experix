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
        ~binIO_t(){fclose(m_file);}
        binIO_t(const char* _fileName, const char* _mode);

        virtual void Open(const char* _fileName, const char* _mode);
        virtual void operator>>(int _intToWrite);
        virtual void operator>>(float _floatToWrite); 
    
    private:

        binIO_t(const binIO_t& ){}
        virtual binIO_t& operator=(const binIO_t& _binIO){} 


};




binIO_t::binIO_t(const char* _fileName, const char* _mode)
{
    if( !(strcmp(_mode, "rb") == 0 || strcmp(_mode, "rb+") == 0 || strcmp(_mode, "wb") == 0 || strcmp(_mode, "wb+") == 0 || strcmp(_mode, "ab") == 0 || strcmp(_mode, "ab+") == 0))
    {
        throw TExeption<int>(0 , __FILE__, __LINE__, "bad mode");
    }
    m_file = fopen(_fileName, _mode);
    if(m_file == 0)
    {
        SetStatus(cant_open_file_e);
         throw TExeption<int>(0 , __FILE__, __LINE__, "error: can't open file");
    }
    SetStatus(ok_e);
}




void binIO_t::Open(const char* _fileName, const char* _mode)
{
    if( !(strcmp(_mode, "rb") == 0 || strcmp(_mode, "rb+") == 0 || strcmp(_mode, "wb") == 0 || strcmp(_mode, "wb+") == 0 || strcmp(_mode, "ab") == 0 || strcmp(_mode, "ab+") == 0))
    {
        throw TExeption<int>(0 , __FILE__, __LINE__, "bad mode");
    }
    if (GetStatus() != ok_e)
    {
        throw TExeption<int>(0 , __FILE__, __LINE__, "error: status of file isn't ok");
    }
    m_file = fopen(_fileName, _mode);
    if (m_file == 0)
    {
        SetStatus(cant_open_file_e);//TODO
        throw TExeption<int>(-1 , __FILE__, __LINE__, "error: can't open file");
    } 
    SetStatus(ok_e);
}




void binIO_t::operator>>(int _intToWrite)
{
    int status = 0;
    void *num = &_intToWrite;
    if (GetStatus() != ok_e)
    {
        throw TExeption<int>(0 , __FILE__, __LINE__, "error: can't write to this file");
    }
    status = fwrite(num, sizeof(int), 1, m_file);
    if (status < 0)
    {
        throw TExeption<int>(0 , __FILE__, __LINE__, "error: writing failed");
    }
    SetSize(); 
}



void binIO_t::operator>>(float _floatToWrite)
{
    int status = 0;
    void *num = &_floatToWrite;
    if (GetStatus() != ok_e)
    {
        throw TExeption<int>(0 , __FILE__, __LINE__, "error: can't write to this file");
    }
    status = fwrite(num, sizeof(int), 1, m_file);
    if (status < 0)
    {
        throw TExeption<int>(0 , __FILE__, __LINE__, "error: writing failed");
    }
    SetSize(); 
}






#endif //__BINIO_T_H__