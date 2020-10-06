#include "i_sensor.hpp"
#include "event_pusher.hpp"
#include "common.hpp"
#include "i_agent.hpp"
#include "event_creator.hpp"
#include "agent_info.hpp"
#include "runnable.hpp"

namespace smartHome {

class FireSensor : public Isensor , public IAgent, public Runnable {
public:
    FireSensor(std::string a_room, std::string a_floor, size_t a_numOfEvents);
    //~FireSensor() = default;

    virtual void Run();
    virtual void SendEvent();
    virtual void Connent(IRegistrar& a_registrar, SharedPtr<EventPusher> a_pusher);
    virtual size_t GetNumOfEventRecived();

private:
    SharedPtr<EventPusher> m_pusher;
    AgentInfo m_agentInfo;
    EventCreator m_eventCreator;
    size_t m_numOfEvents;
    static int m_id;


};

}//smartHome