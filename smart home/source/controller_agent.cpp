#include "controller_agent.hpp"
#include <iostream>
#include "common.hpp"

namespace smartHome {

ControllerAgent::ControllerAgent(std::string a_id, std::string a_type, std::string a_log,
                                 std::string a_room, std::string a_floor)
    : m_agentInfo(a_id, a_type, a_log, a_room, a_floor)
    , m_subcribeList()
    , m_numOfEvents(0)
    , m_eventCont()
{
    m_subcribeList.push_back(std::make_pair((a_type), Location(a_room, a_floor)));
}

void ControllerAgent::AddTypeToRegister(Type a_type, Location a_location) {
    m_subcribeList.push_back(std::make_pair(a_type, a_location));
}

void ControllerAgent::SubcribeSelf(DistributionList& a_dl) {
    SubcribeList::iterator begin = m_subcribeList.begin();
    SubcribeList::iterator end = m_subcribeList.end();
    SharedPtr<ControllerAgent> self = shared_from_this();
    while (begin != end) {
        a_dl.AddController(self, begin->first, begin->second);
        ++begin;
    }
}


void ControllerAgent::HandleEvent(SharedPtr<Event> a_event) {
    //a_event->Print(); 
    m_eventCont.push_back(m_agentInfo.GetId());
    ++m_numOfEvents;
}

size_t ControllerAgent::GetNumOfEventsRecived() const {
    return m_numOfEvents;
}

EventsContainer ControllerAgent::GetEventContainer() {
    return m_eventCont;
}

void ControllerAgent::Connent(IRegistrar& a_registrar, SharedPtr<EventPusher> a_pusher) {
    Location loc(m_agentInfo.GetRoom(), m_agentInfo.GetFloor());
    Type type(m_agentInfo.GetType());
    SharedPtr<IEventHandler> self = shared_from_this();
    a_registrar.AddController(self, type, loc);
}

size_t ControllerAgent::GetNumOfEventRecived() {
    return m_eventCont.size();
}

}//smartHome