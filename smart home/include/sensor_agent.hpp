#ifndef SENSOR_AGENT_HPP
#define SENSOR_AGENT_HPP
#include "i_sensor.hpp"
#include "event_pusher.hpp"
#include "agent_info.hpp"
#include "event_creator.hpp"
#include "runnable.hpp"
#include "thread.hpp"

namespace smartHome{

class SensorAgent : public Isensor {
public:
    SensorAgent(SharedPtr<EventPusher> a_eventPusher, std::string a_id, std::string a_type, std::string a_log,
                std::string a_room, std::string a_floor);
    ~SensorAgent();

    void StartSensor(size_t a_numOfE);
    virtual void SendEvent();

private:
    SharedPtr<EventPusher> m_eventPusher;
    AgentInfo m_agentInfo;
    EventCreator m_eventCreator;
    //SharedPtr<Runnable> m_sensorRunnable;
    //Thread m_sensorThread;
};

}//smartHome

#endif // SENSOR_AGENT_HPP