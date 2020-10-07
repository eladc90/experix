#include <sstream>
#include "sensor_utils.hpp"

namespace smartHome {

SensorRunnable::SensorRunnable(SharedPtr<EventPusher> a_eventPusher,  SharedPtr<Event> a_event, size_t a_numofEvents) 
    : m_pusher(a_eventPusher)
    , m_event (a_event)
    , m_numOfEvents(a_numofEvents)
{
}

SensorRunnable::~SensorRunnable() 
{
}

std::string IntToString (int a_number ) {
    std::ostringstream ss;
    ss << a_number;
    return ss.str();
}


void SensorRunnable::Run() {
    static int i = 0;
    while (m_numOfEvents) {
        ++i;
        ID id(IntToString(i));
        Type type = m_event->GetType();
        Location location = m_event->GetLocation();
        SharedPtr<Event> newEvent(new Event(id , type, location));
        m_pusher->PushEvent(newEvent); 
        --m_numOfEvents;
    }
}


}//smartHome