#ifndef CONTROLLER_AGENT_HPP
#define CONTROLLER_AGENT_HPP
#include <vector>
#include "i_controller.hpp"
#include "agent_info.hpp"
#include "common.hpp"
#include "distributaion_list.hpp"
#include "I_event_handler.hpp"
#include "i_agent.hpp"

namespace smartHome {

typedef std::vector<std::pair<Type, Location> > SubcribeList;
typedef std::vector<std::string> EventsContainer;

class ControllerAgent : public Icontroller, public IEventHandler, public IAgent
    , public std::tr1::enable_shared_from_this<ControllerAgent> {
public:
    ControllerAgent(std::string a_id, std::string a_type, std::string a_log, std::string a_room,
                    std::string a_floor);
    //~ControllerAgent = default;

    virtual void HandleEvent(SharedPtr<Event> a_event);
    virtual void SubcribeSelf(DistributionList& a_dl);
    size_t GetNumOfEventsRecived() const;
    void AddTypeToRegister(Type a_type, Location a_location);
    EventsContainer GetEventContainer();
    virtual void Connent(IRegistrar& a_registrar, SharedPtr<EventPusher> a_pusher);

    virtual size_t GetNumOfEventRecived();
    
private:
    AgentInfo m_agentInfo;
    SubcribeList m_subcribeList;
    size_t m_numOfEvents;
    EventsContainer m_eventCont;


};

}//smartHome

#endif // CONTROLLER_AGENT_HPP