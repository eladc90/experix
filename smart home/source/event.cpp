#include "event.hpp"
#include <iostream>

namespace smartHome {



Event::Event(ID& a_id, Type& a_type, Location& a_location)
    : m_id(a_id)
    , m_type(a_type)
    , m_location(a_location)
{
}

Event::~Event() 
{
}

const ID& Event::GetId() const NOEXCEPTIONS{
    return m_id;
}  

const Type& Event::GetType() const NOEXCEPTIONS{
    return m_type;
}

Location Event::GetLocation() NOEXCEPTIONS{
    return m_location;
}

}// smartHome