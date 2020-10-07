#include "memManager_t.h"



bool MemManager_t::IsEmpty()const
{
    if (m_actualSize == 0)
    {
        return true;
    }
    return false;
}

void MemManager_t::SetPosition(size_t _pos)
{
    if (_pos > m_actualSize)
    {
            throw false;
    }
    m_position = _pos;     

}

void MemManager_t::SetActualSize(size_t _actualSize)
{
    if (_actualSize > m_actualSize)
    {
        m_actualSize = _actualSize;
    }    
}

