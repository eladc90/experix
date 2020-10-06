#include "agent_info.hpp"

namespace smartHome {

AgentInfo::AgentInfo(std::string a_id, std::string a_type, std::string a_log, std::string a_room, std::string a_floor)
    : m_id(a_id)
    , m_type(a_type)
    , m_log(a_log)
    , m_room(a_room)
    , m_floor(a_floor)
{
}

AgentInfo::~AgentInfo() 
{
}

std::string AgentInfo::GetId() const {
    return m_id;
}

std::string AgentInfo::GetType() const{
    return m_type;
}

std::string AgentInfo::GetLog() const{
    return m_log;
}

std::string AgentInfo::GetRoom() const{
    return m_room;
}

std::string AgentInfo::GetFloor() const{
    return m_floor;
}


}//smartHome