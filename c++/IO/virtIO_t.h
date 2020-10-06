#ifndef __VIRTIO_T_H__
#define __VIRTIO_T_H__


#include <string>
#include <stdio.h>
#include "exHand.h"

using namespace std;


enum f_status
{
    	ok_e, 
		cant_open_file_e, 
		bad_access_e, 
		writeErr_e,
        readErr_e
};

class virtIO_t
{
    public:

        virtIO_t(){m_status = ok_e;}
        virtIO_t(const char* _name,const char* _mode);
        virtual ~virtIO_t(){}

        virtual void        Open(const char* _fileName, const char* _mode) = 0; 

        f_status            Close()                         {fclose(m_file);}
        const string        GetPath()const                  {return m_path;} // TODO
        const  string       GetExcessStat()const            {return m_acessMod;}
        size_t              FileSize()                      {return m_size;}
        long int            GetPosition()const              {return ftell(m_file);}
        f_status            GetStatus()const                {return m_status;}
        const int           GetSize()                       {return m_size;}
        virtual void        SetStatus(f_status _status)     {m_status = _status;}
        void                SetSize();
        int                 SetPosition(int _ind);

        virtual void operator>>(int _intToWrite) = 0;
        virtual void operator>>(float _floatToWrite) = 0;
       /*  virtual void operator>>(int) = 0;  */

        /* virtual const virtIO_t& operator<<(float) = 0;
        virtual const virtIO_t& operator>>(float) = 0; */

        FILE*       m_file;

    protected:

        virtIO_t(const virtIO_t& _vIO){;}
        virtual virtIO_t& operator=(const virtIO_t& x){};

    private:

        string      m_name;
        string      m_acessMod;
        string      m_path;
        size_t      m_size;
        f_status    m_status;

};


virtIO_t::virtIO_t(const char* _name,const char* _mode)
{
    m_name = _name;
    m_acessMod = _mode;
    m_status = ok_e;
    m_size = 0;
}


int virtIO_t::SetPosition(int _position)
{
    if (_position > m_size)
    {
        throw TExeption<int>(0 , __FILE__, __LINE__, "invalid position"); 
    }
    if (fseek(m_file, _position, SEEK_SET) != 0)
    {
        throw TExeption<int>(0 , __FILE__, __LINE__, "set position failed");
    }
}

void virtIO_t::SetSize()//TODO 
{
    int tmpPosition = GetPosition();
    fseek(m_file, 0, SEEK_END); 
    m_size = ftell(m_file);
    SetPosition(tmpPosition);
}



#endif //__VIRTIO_T_H__
