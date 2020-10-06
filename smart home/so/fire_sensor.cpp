#include <sstream>
#include "fire_sensor.hpp"
#include "event.hpp"
#include "thread.hpp"

namespace smartHome {

int FireSensor::m_id = 0;

std::string IdToString (int a_number ) {
    std::ostringstream ss;
    ss << a_number;
    return ss.str();
}

FireSensor::FireSensor(std::string a_room, std::string a_floor, size_t a_numOfEvents) 
    : m_pusher ()
    , m_agentInfo(IdToString(m_id), "fire", "log", a_room, a_floor)
    , m_eventCreator(m_agentInfo)
    , m_numOfEvents(a_numOfEvents)
{
    ++m_id;
}

void FireSensor::Run() {

    while (m_numOfEvents) {
        SendEvent();
        --m_numOfEvents;
    }
}

void FireSensor::SendEvent() {
    SharedPtr<Event> event(new Event(m_eventCreator.CreateEvent())); 
    m_pusher->PushEvent(event);
}

void FireSensor::Connent(IRegistrar& a_registrar, SharedPtr<EventPusher> a_pusher) {
    m_pusher = a_pusher;
    SharedPtr<Thread> fireSensorThread(new Thread(*this));
}

size_t FireSensor::GetNumOfEventRecived() {
    return 0;
}


}//smartHome