#include "sensor_agent.hpp"
#include "sensor_utils.hpp"

namespace smartHome{

SensorAgent::SensorAgent(SharedPtr<EventPusher> a_eventPusher, std::string a_id, std::string a_type, std::string a_log,
                std::string a_room, std::string a_floor)
    :m_eventPusher(a_eventPusher)
    , m_agentInfo(a_id, a_type, a_log, a_room, a_floor)
    , m_eventCreator(m_agentInfo)
    //, m_sensorRunnable(new SensorRunnable(*this, 1))
    //, m_sensorThread(*m_sensorRunnable)
{
}

SensorAgent::~SensorAgent() 
{
}

void SensorAgent::SendEvent() {
    m_eventPusher->PushEvent(SharedPtr<Event>(new Event(m_eventCreator.CreateEvent()))); 
}

void SensorAgent::StartSensor(size_t a_numOfE) {
    SharedPtr<Runnable> sensorRunnable(new SensorRunnable(m_eventPusher, SharedPtr<Event>(new Event(m_eventCreator.CreateEvent())), a_numOfE));
    Thread sensorThread(*sensorRunnable);
    sensorThread.Join();
}

}//smartHome