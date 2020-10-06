#ifndef __ASCIIIO_T_H__
#define __ASCIIIO_T_H__


#include <string>
#include <stdio.h>
#include <string.h>
#include "virtIO_t.h"

using namespace std;


class asciiIO_t : public virtIO_t
{
    public:

        asciiIO_t(){}
        ~asciiIO_t(){fclose(m_file);}
        asciiIO_t(const char* _fileName, const char* _mode);

        virtual void Open(const char* _fileName, const char* _mode); 

        virtual void operator>>(int _intToWrite);
        virtual void operator>>(float _floatToWrite); 
        /* virtual void operator>>(int);  */

    private:

        asciiIO_t(const asciiIO_t& x){;}
        virtual asciiIO_t& operator=(const asciiIO_t& _ascii){};

};



asciiIO_t::asciiIO_t(const char* _fileName, const char* _mode)
{
    if( !(strcmp(_mode, "r") == 0 || strcmp(_mode, "r+") == 0 || strcmp(_mode, "w") == 0 || strcmp(_mode, "w+") == 0 || strcmp(_mode, "a") == 0 || strcmp(_mode, "a+") == 0))
    {
        throw TExeption<int>(0 , __FILE__, __LINE__, "bad mode");
    }
    m_file = fopen(_fileName, _mode);
    if (m_file == 0)
    {
        SetStatus(cant_open_file_e);
        throw TExeption<int>(0 , __FILE__, __LINE__, "error: can't open file");
    } 
    SetStatus(ok_e);
}


void asciiIO_t::Open(const char* _fileName, const char* _mode)
{
    if( !(strcmp(_mode, "r") == 0 || strcmp(_mode, "r+") == 0 || strcmp(_mode, "w") == 0 || strcmp(_mode, "w+") == 0 || strcmp(_mode, "a") == 0 || strcmp(_mode, "a+") == 0))
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
        SetStatus(cant_open_file_e);
        throw TExeption<int>(0 , __FILE__, __LINE__, "error: can't open file");
    } 
    SetStatus(ok_e);
}




void asciiIO_t::operator>>(int _intToWrite)
{
    int status = 0;
    if (GetStatus() != ok_e)
    {
        throw TExeption<int>(0 , __FILE__, __LINE__, "error: can't write to this file");
    }
    status = fprintf(m_file, "%d", _intToWrite);
    if (status < 0)
    {
        throw TExeption<int>(-1 , __FILE__, __LINE__, "error: writing to file failed");
    }
    SetSize(); 
}


void asciiIO_t::operator>>(float _floatToWrite)
{
    int status = 0;
    if (GetStatus() != ok_e)
    {
        throw TExeption<int>(0 , __FILE__, __LINE__, "error: can't write to this file");
    }
    status = fprintf(m_file, "%f", _floatToWrite);
    if (status < 0)
    {
        throw TExeption<int>(-1 , __FILE__, __LINE__, "error: writing to file failed");
    }
    SetSize(); 
}


/* int asciiIO_t :: operator<<(int)
{
 
    int buf = 0;
    fscanf(GetFile(),"%d",&buf);
    printf("this  is the buff%d", buf);
    return buf;
 
} */






#endif //__ASCIIIO_T_H__