#include "memPage_t.h"
#include <string.h>
 
size_t MemPage_t::mg_defCapacity = 6;



MemPage_t::MemPage_t():MemManager_t()
{
    m_page = new char [mg_defCapacity];
    m_capacity = mg_defCapacity;
    SetPosition(0);
    SetActualSize(0);
}



MemPage_t::MemPage_t(size_t _capacity):MemManager_t()
{
    if (_capacity == 0)
    {
        _capacity = mg_defCapacity; // TODO
    }
    m_page = new char [_capacity];
    m_capacity = _capacity;
    SetPosition(0);
    SetActualSize(0);
}



MemPage_t::~MemPage_t()
{
   ;
}



byte MemPage_t::Read(const void *_buffer, size_t nBytes)
{
    byte numOfByte = MyRead(_buffer, GetPosition(), nBytes);
    return numOfByte;
}



byte MemPage_t::Read(const void *_buffer, size_t _from, size_t nBytes)
{
    byte numOfByte = MyRead(_buffer, _from, nBytes);
    return numOfByte;
}



byte MemPage_t::Write(const void *_buffer, size_t nBytes)
{
    byte numOfByte = MyWrite(_buffer, GetPosition(), nBytes);
    return numOfByte;
}



byte MemPage_t::Write(const void *_buffer, size_t _from, size_t nBytes)
{
    byte numOfByte = MyWrite(_buffer, _from, nBytes);
    return numOfByte;
}



byte MemPage_t::MyRead(void *_buffer, size_t _from, size_t nBytes)
{
    if(_from > GetActualSize() || !_buffer)
    {
        return 0;
    }
    if (_from + nBytes > GetActualSize())
    {
        memcpy(_buffer, m_page + _from, GetActualSize() - _from);
        
        try
        {
            SetPosition(_from + GetActualSize() - _from);
        }
        catch(bool ex)
        {
            cout << "invalid set position" << endl;
        } 
        return GetActualSize() - _from;
    }
    else
    {
        memcpy(_buffer, m_page + _from, nBytes);
        SetPosition(_from + nBytes);
        return nBytes;
    }
    
}



byte MemPage_t::MyWrite(void *_buffer, size_t _from, size_t nBytes)
{
    if(_from > GetActualSize() || !_buffer)
    {
        return 0;
    }
    if (_from + nBytes > m_capacity)
    {
        memcpy( m_page + _from, _buffer, m_capacity - _from);
        SetActualSize(_from + nBytes);
        try
        {
            SetPosition(m_capacity - _from);
        }
        catch(bool ex)
        {
            cout << "invalid set position" << endl;
        } 
        
        return m_capacity - _from;
    }
    else
    {
        memcpy(m_page + _from, _buffer, nBytes);
        SetActualSize(_from + nBytes);
        try
        {
            SetPosition(_from + nBytes);
        }
        catch(bool ex)
        {
            cout << "invalid set position" << endl;
        } 
        
        return nBytes;
    }
}





