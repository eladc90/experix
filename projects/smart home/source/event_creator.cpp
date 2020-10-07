#include "event_creator.hpp"

namespace smartHome {
    
EventCreator::EventCreator(AgentInfo& a_info)
    : m_info(a_info)
{
}

Event EventCreator::CreateEvent() NOEXCEPTIONS{
    ID eventId(m_info.GetId());
    Type eventType(m_info.GetType());
    Location eventLocation(m_info.GetRoom(), m_info.GetFloor());
    Event newEvent(eventId, eventType, eventLocation);
    return newEvent;
}

}//smartHome