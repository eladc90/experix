#ifndef AGENT_INFO_HPP
#define AGENT_INFO_HPP
#include <string>
namespace smartHome {

class AgentInfo {
public:
    AgentInfo(std::string a_id, std::string a_type, std::string a_log, std::string a_room, std::string a_floor);
    ~AgentInfo();

    std::string GetId()const;
    std::string GetType()const;
    std::string GetLog()const;
    std::string GetRoom()const;
    std::string GetFloor()const;

private:
    std::string m_id;
    std::string m_type;
    std::string m_log;
    std::string m_room;
    std::string m_floor;

};

}// smartHome

#endif // !AGENT_INFO_HPP