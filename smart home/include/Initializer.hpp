#ifndef INITIALIZER_HPP
#define INITIALIZER_HPP
#include <string>
#include <vector>
#include "i_controller.hpp"
#include "i_sensor.hpp"
#include "distributaion_list.hpp"
#include "hub.hpp"
#include "config_parser.hpp"

namespace smartHome{
typedef std::vector<SharedPtr<IAgent> > AgentContainer;


class Initializer {
public:
    explicit Initializer(std::string a_configFile);
    //~Initializer() = default;

    void LoadControllersAndSensors();
    void SubcribeAgents(Server& a_server);
    size_t GetNumOfControllers();
    size_t GetNumOfSensors();

    AgentContainer& GetAgentCont();// for testing
private:
    
    void CreateController(std::string a_funcName, void *a_handle);
    void CreateSensor(std::string a_funcName, void *a_handle);
    void CreateAgent(std::string a_funcName, std::string a_room, std::string a_floor, void *a_handle);


private:
    std::string m_configFile;
    AgentContainer m_agentCont;
    ConfigParser m_parser;

};

}//smartHome

#endif // INITIALIZER_HPP