#include <dlfcn.h>
#include <iostream>
#include "type.hpp"
#include "location.hpp"
#include "i_controller.hpp"
#include "event_bus.hpp"
#include "event_puller.hpp"
#include "event_pusher.hpp"
#include "hub.hpp"
#include "Initializer.hpp"
#include "i_sensor.hpp"
#include "i_agent.hpp"
#include "mu_test.h"
#include "server.hpp"

using namespace smartHome;


//-------------------------------- creating funcs ------------------------------------//


size_t GetNumOfEvents(AgentContainer& a_agents) {
    AgentContainer::iterator begin = a_agents.begin();
    AgentContainer::iterator end = a_agents.end();
    size_t sum = 0;
    while (begin != end) {
        sum += (*begin)->GetNumOfEventRecived();
        ++begin;
    }
    return sum;
}

SharedPtr<IAgent> MakeSprinklerController(std::string a_room, std::string a_floor) {

    SharedPtr<IAgent> (*createSprinkler)(std::string a_room, std::string a_floor);
    void *handle = dlopen("./lib_controllers.so", RTLD_NOW);
    if (!handle) {
        std::cout << dlerror() << std::endl;
    }

    createSprinkler = (SharedPtr<IAgent> (*)(std::string a_room, std::string a_floor))dlsym(handle, "CreatingSprinkel");
    if (!createSprinkler) {
        std::cout << dlerror() << std::endl;
    }
    SharedPtr<IAgent> sprinkler = createSprinkler(a_room, a_floor);
    return sprinkler;
}


SharedPtr<IAgent> MakeDoorController(std::string a_room, std::string a_floor) {

    SharedPtr<IAgent> (*createDoor)(std::string a_room, std::string a_floor);
    void *handle = dlopen("./lib_controllers.so", RTLD_NOW);
    if (!handle) {
        std::cout << dlerror() << std::endl;
    }

    createDoor = (SharedPtr<IAgent> (*)(std::string a_room, std::string a_floor))dlsym(handle, "CreatingDoor");
    if (!createDoor) {
        std::cout << dlerror() << std::endl;
    } 
    SharedPtr<IAgent> door = createDoor(a_room, a_floor);
    return door;
}


SharedPtr<IAgent> MakeFireSensor(std::string a_id, std::string a_room, std::string a_floor, size_t a_numOfEvents) {

    SharedPtr<IAgent> (*createSensor)(std::string a_id, std::string a_room, std::string a_floor, size_t a_numOfEvents);
    void *handle = dlopen("./lib_controllers.so", RTLD_NOW);
    if (!handle) {
        std::cout << dlerror() << std::endl;
    }

    createSensor = (SharedPtr<IAgent> (*)(std::string a_id, std::string a_room, std::string a_floor, size_t a_numOfEvents))dlsym(handle, "CreatingFireSensor");
    if (!createSensor) {
        std::cout << dlerror() << std::endl;
    }
    SharedPtr<IAgent> sensor = createSensor(a_id, a_room, a_floor, a_numOfEvents);
    return sensor;
}

//------------------------------- tests -----------------------------------//

UNIT(check_so_basic)
    SharedPtr<IAgent> (*createSprinkler)(std::string a_room, std::string a_floor);
    SharedPtr<IAgent> (*createDoor)(std::string a_room, std::string a_floor);
    SharedPtr<IAgent> (*createSensor)(std::string a_room, std::string a_floor);
    void *handle = dlopen("./lib_controllers.so", RTLD_NOW);
    if (!handle) {
        std::cout << dlerror() << std::endl;
    }

    createSprinkler = (SharedPtr<IAgent> (*)(std::string a_room, std::string a_floor))dlsym(handle, "CreatingSprinkel");
    if (!createSprinkler) {
        std::cout << dlerror() << std::endl;
    }

    createDoor = (SharedPtr<IAgent> (*)(std::string a_room, std::string a_floor))dlsym(handle, "CreatingDoor");
    if (!createDoor) {
        std::cout << dlerror() << std::endl;
    } 

    createSensor = (SharedPtr<IAgent> (*)(std::string a_room, std::string a_floor))dlsym(handle, "CreatingFireSensor");
    if (!createSensor) {
        std::cout << dlerror() << std::endl;
    }

    SharedPtr<IAgent> sprinkler = MakeDoorController("1", "1");
    //dlclose(handle);
    ASSERT_THAT(handle);
    ASSERT_THAT(createDoor);
    ASSERT_THAT(sprinkler);
END_UNIT

UNIT(controller_1_sensors_1) 
    //init test
    const size_t eventQueueSize = 20;
    Server server(eventQueueSize);
    Hub hub(server);

    //load and create agents
    size_t numOfEvents = 2;
    SharedPtr<IAgent> fireSensor = MakeFireSensor("1", "1", "1", numOfEvents);
    SharedPtr<IAgent> fireController = MakeSprinklerController("1", "1");
    SharedPtr<IAgent> fireControllerFloor = MakeSprinklerController("*", "1");

    server.AddAgent(fireControllerFloor);
    server.AddAgent(fireController);

    server.AddAgent(fireSensor);
    //send events
    sleep(1);
    hub.ShutDownHub();
    
    ASSERT_THAT(1);
END_UNIT

UNIT(parse_test) 
    //init test
    const size_t eventQueueSize = 20;
    Server server(eventQueueSize);
    Hub hub(server);

    std::string confFile = "config_file";
    Initializer initi(confFile);
    initi.LoadControllersAndSensors();
    initi.SubcribeAgents(server);


    AgentContainer& agents = initi.GetAgentCont();
    
    sleep(1);
    size_t sum = GetNumOfEvents(agents);
    hub.ShutDownHub();
    size_t numOfEventsExpected = 20;
    ASSERT_THAT(sum == numOfEventsExpected);
END_UNIT

UNIT(recive_event_test) 
    //init test
    const size_t eventQueueSize = 20;
    Server server(eventQueueSize);
    Hub hub(server);

    std::string confFile = "controller_3";
    Initializer initi(confFile);
    initi.LoadControllersAndSensors();
    initi.SubcribeAgents(server);


    
    sleep(1);
    AgentContainer& agents = initi.GetAgentCont();
    size_t sum = GetNumOfEvents(agents);
    hub.ShutDownHub();
    size_t numOfEventsExpected = 40;
    ASSERT_THAT(sum == numOfEventsExpected);
END_UNIT

UNIT(server_test) 
    //init test
    const size_t eventQueueSize = 20;
    Server server(eventQueueSize);
    Hub hub(server);

    std::string confFile = "controller_3";
    Initializer initi(confFile);
    initi.LoadControllersAndSensors();
    initi.SubcribeAgents(server);


    
    sleep(1);
    AgentContainer& agents = initi.GetAgentCont();
    size_t sum = GetNumOfEvents(agents);
    hub.ShutDownHub();
    size_t numOfEventsExpected = 40;
    ASSERT_THAT(sum == numOfEventsExpected);
END_UNIT


TEST_SUITE(mvp)
    TEST(check_so_basic) 
    TEST(controller_1_sensors_1)
    TEST(parse_test) 
    TEST(recive_event_test) 
    TEST(server_test) 
END_SUITE 


