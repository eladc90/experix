#include "memPage_t.h"
#include "memPool_t.h"
#include <vector>


memPool_t::memPool_t():MemManager_t()
{
    MemPage_t *pagePtr = new MemPage_t;
    m_pool.push_back(pagePtr);
    SetPosition(0);
    SetActualSize(0);
    m_pageCapacity = m_pool[0] -> GetCapacity();
}


memPool_t::memPool_t(size_t _capacity):MemManager_t()
{
    if (_capacity == 0)
    {
        _capacity = MemPage_t::GetGCapacity();
    }
    MemPage_t *pagePtr = new MemPage_t(_capacity);
    m_pool.push_back(pagePtr);
    SetPosition(0);
    SetActualSize(0);
     m_pageCapacity = _capacity;
}


memPool_t::~memPool_t()
{
    size_t i = 0;
    for (i; i < m_pool.size() ; i++)
    {
        delete m_pool[i];
    }
}


byte memPool_t::Read(const void *_buffer, size_t nBytes)
{
    return MyRead(_buffer, GetPosition(), nBytes);
}


byte memPool_t::Read(const void *_buffer, size_t _from, size_t nBytes)
{
    return MyRead(_buffer, _from, nBytes);
}


byte memPool_t::Write(const void *_buffer, size_t nBytes)
{
    return MyWrite(_buffer, GetPosition(), nBytes);
}


byte memPool_t::Write(const void *_buffer, size_t _from, size_t nBytes)
{
    return MyWrite(_buffer, _from, nBytes);
}


byte memPool_t:: MyRead(const void *_buffer, size_t _from, size_t nBytes)
{
    size_t readByte = 0;
    size_t index = _from/m_pageCapacity;
    size_t sumBytes = 0;
    size_t currPos = _from % m_pageCapacity;

    try
    {
        SetPosition(_from);
    }
    catch(bool ex)
    {
        cout << "invalid set position" << endl;
        return 0;
    }

    if (!_buffer)
    {
        return 0;
    }

    nBytes = (GetActualSize() - _from) < nBytes ? GetActualSize() - _from : nBytes;

    while(nBytes != 0)
    {
        readByte = m_pool[index++]->Read(_buffer, currPos, nBytes);
        _buffer = (char *)_buffer + readByte;
        sumBytes += readByte;
        nBytes -= readByte;
        currPos = 0;
    }
    SetPosition(_from + sumBytes);
    return sumBytes;
}


byte memPool_t:: MyWrite(void *_buffer, size_t _from, size_t nBytes)
{
    size_t writeByte = 0;
    size_t index = _from /m_pageCapacity;
    size_t sumBytes = 0;
    size_t totalBytes = _from + nBytes;
    size_t totalCapacity = 0;
    size_t addPages = 0;
    size_t currPos = _from % m_pageCapacity;

    if (!_buffer || _from > GetActualSize())
    {
        return 0;
    }

    totalCapacity = m_pageCapacity *m_pool.size();

    if (totalBytes > totalCapacity)
    {
        addPages = ((totalBytes - totalCapacity) /  m_pageCapacity) + 1;
    }

    while(addPages--)
    {
        MemPage_t *pagePtr = new MemPage_t(m_pageCapacity);
        m_pool.push_back(pagePtr);
    }
    
    
    while(nBytes != 0)
    {
        writeByte = m_pool[index++] -> Write(_buffer , currPos, nBytes);
        _buffer = (char *)_buffer + writeByte;
        sumBytes += writeByte;
        nBytes -= writeByte;
        currPos = 0;
    }
    SetActualSize(totalBytes);
    SetPosition(_from + sumBytes);
    return sumBytes;
}
