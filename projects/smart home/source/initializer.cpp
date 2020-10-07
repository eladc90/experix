#include <iostream>
#include <dlfcn.h>
#include <fstream>
#include "Initializer.hpp"
#include "i_agent.hpp"

namespace smartHome {

Initializer::Initializer(std::string a_configFile)
    : m_configFile(a_configFile)
    , m_agentCont()
    , m_parser()
{
}

void Initializer::LoadControllersAndSensors() {
    void *handle = dlopen("./lib_controllers.so", RTLD_NOW);
    if (!handle) {
        std::cout << dlerror() << std::endl;
    }

    std::string agent;
    std::ifstream configFile(m_configFile.c_str());
    if (configFile.is_open())
    {
        while (getline (configFile,agent) )
        {
            m_parser.ParseLine(agent);
            CreateAgent(m_parser.GetFunc(), m_parser.GetRoom(), m_parser.GetFloor(), handle); 
            
        }
        configFile.close();
    }
}

void Initializer::CreateAgent(std::string a_funcName, std::string a_room, std::string a_floor, void *a_handle) {

    SharedPtr<IAgent> (*create)(std::string a_room, std::string a_floor);
    create = (SharedPtr<IAgent> (*)(std::string a_room, std::string a_floor))dlsym(a_handle, a_funcName.c_str());
    if (!create) {
        std::cout << dlerror() << std::endl;
    }
    SharedPtr<IAgent> controller = create(a_room, a_room);
    m_agentCont.push_back(controller);
}


void Initializer::SubcribeAgents(Server& a_server) {
    AgentContainer::iterator begin = m_agentCont.begin();
    AgentContainer::iterator end = m_agentCont.end();
    while (begin != end) {
        a_server.AddAgent(*begin);
        ++begin;
    } 
}

size_t Initializer::GetNumOfControllers() {
    return m_agentCont.size();
}

AgentContainer& Initializer::GetAgentCont() {
    return m_agentCont;
}

}//smartHome