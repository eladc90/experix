#ifndef EVENT_CREATOR_HPP
#define EVENT_CREATOR_HPP
#include "agent_info.hpp"
#include "event.hpp"
#include "location.hpp"
#include "type.hpp"
#include "payload.hpp"
#include "id.hpp"

namespace smartHome {

class EventCreator {
public:
    EventCreator(AgentInfo& a_info);
    //~EventCreator() = default;

    Event CreateEvent() NOEXCEPTIONS;
private:
    AgentInfo& m_info;
};

}//smartHome


#endif // !EVENT_CREATOR_HPP