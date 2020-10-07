#include <iostream> 
#include <sstream>
#include "mu_test.h"
#include "event.hpp"
#include "id.hpp"
#include "WaitableBoundedQueue.hpp"
#include "event_pusher.hpp"
#include "sensor_agent.hpp"
#include "event_puller.hpp"
#include "common.hpp"
#include "dispatcher.hpp"
#include "distributaion_list.hpp"
#include "hub.hpp"
#include "event_bus.hpp"
#include "i_controller.hpp"
#include "server.hpp"

using namespace smartHome;

//-------------------------------- type defs ------------------------------------//


typedef WaitableBoundedQueue<SharedPtr<Event> > eventBus;
typedef std::string EventType;
typedef std::vector<SharedPtr<ControllerAgent> > ControllersVector;
typedef std::vector<SharedPtr<SensorAgent> > SensorVector;


const int sizeOfTypeArray = 4;
const int sizeOfLocationArray = 12;
const int sizeOfLocationArrayNoFloor = 9;
const int sizeOfFloorLocationArray = 3; 


//-------------------------------- using arrays ------------------------------------//


const Type typeArray[sizeOfTypeArray] = {Type("fire"), Type("fire"), Type("doors"), Type("water sprinkler")}; 

const Location RoomlocationArray[sizeOfLocationArray] = {Location ("1", "1"), Location ("2", "1"), Location ("3", "1"),
                                  Location ("2", "2"), Location ("2", "2"), Location ("3", "2"),
                                  Location ("1", "3"), Location ("2", "3"), Location ("3", "3"),
                                  Location ("*", "1"), Location ("*", "2"), Location ("*", "3")};

const Location FloorlocationArray[sizeOfFloorLocationArray] = {Location ("*", "1"), Location ("*", "2"), Location ("*", "3")};

const std::string idArray[] = {"1", "2", "3","4","5","6","7","8", "9", "10", "11", "12"};

const Location AllLocation = Location ("*", "*");
const Type AllType = Type("*");


//----------------------------- aux functions declaration -----------------------//


ControllersVector MakeControllers(size_t a_numOfControllers);
SharedPtr<ControllerAgent> MakeController(Type a_eventType, Location a_location, std::string a_id);
std::vector<SharedPtr<SensorAgent> > MakeSensors(EventPusher& a_eventPusher);
SharedPtr<SensorAgent> makeSensor(SharedPtr<EventPusher> a_eventPusher, std::string a_id, Type a_eventType, Location a_location);
std::string IntToString (int a_number );
int StringToINt (std::string a_number );


//----------------------------- aux functions ---------------------------------//


ControllersVector MakeControllers() {
    ControllersVector controllerVec;
    int numOfController = 9;
    for (int i = 0; i < numOfController; ++ i) {
        SharedPtr<ControllerAgent> newController =  MakeController(typeArray[i % sizeOfTypeArray],RoomlocationArray[i], idArray[i]);
        controllerVec.push_back(newController);
    }
    return controllerVec;
}

std::vector<SharedPtr<SensorAgent> > MakeSensors(SharedPtr<EventPusher> a_eventPusher) {
    SensorVector SensorVec;
    static int runnigNum = 0;
    int numOfSensors = 9;
    for (int i = 0; i < numOfSensors; ++i) {

        SharedPtr<SensorAgent> newController =  makeSensor(a_eventPusher, IntToString(runnigNum), typeArray[i % sizeOfTypeArray],
                                                            RoomlocationArray[i]);
        SensorVec.push_back(newController);
        ++runnigNum;
    }
    return SensorVec;  
}

SharedPtr<ControllerAgent> MakeController(Type a_eventType, Location a_location, std::string a_id) {
    return SharedPtr<ControllerAgent>( new ControllerAgent(a_id, a_eventType.GetType(),
                                        "log", a_location.GetRoom(), a_location.GetFloor()));     
}

SharedPtr<SensorAgent> makeSensor(SharedPtr<EventPusher> a_eventPusher, std::string a_id, Type a_eventType, Location a_location) {
    static unsigned int runningNum = 0;
    ++runningNum;
    return SharedPtr<SensorAgent>(new SensorAgent(a_eventPusher, a_id, a_eventType.GetType(), "log",
                                   a_location.GetRoom(), a_location.GetFloor()));
}

void AddAgentsToHub(Server& a_server, ControllersVector a_controllers) {
    ControllersVector::iterator begin = a_controllers.begin();
    ControllersVector::iterator end = a_controllers.end();
    while (begin != end) {
        a_server.AddAgent(*begin);
        ++begin;
    }
}
void SendEvents(SensorVector a_sensors, size_t a_numOfEvents) {
    SensorVector::iterator begin = a_sensors.begin();
    SensorVector::iterator end = a_sensors.end();
    while (begin != end) {
        (*begin)->StartSensor(a_numOfEvents);
        ++begin;
    }
}

SharedPtr<ControllerAgent> MakeWildCard() {
    return MakeController(AllType, AllLocation, "1");
}

int SumReciveEvents(ControllersVector& a_controllers) {
    ControllersVector::iterator begin = a_controllers.begin();
    ControllersVector::iterator end = a_controllers.end();
    int sum = 0;
    while (begin != end) {
        sum += (*begin)->GetNumOfEventsRecived();
        ++begin;
    }
    return sum;
}


bool CheckRunningEqual(int a_b) {
    static int i = 0;
    ++i;
    if (i > a_b) {
        i = a_b;
    }
    return i == a_b;
}

std::string IntToString (int a_number ) {
    std::ostringstream ss;
    ss << a_number;
    return ss.str();
}

int StringToINt (std::string a_number ) {
    std::stringstream a_num(a_number);
    int num = 0;
    a_num >> num;
    return num;
}


class CheckEvent {
public:
    CheckEvent() : m_runningNum(0) {}
    bool operator()(std::string a_num){

        int i = StringToINt(a_num);
        return CheckRunningEqual(i);
    }
private:
    int m_runningNum;
};


int CheckControllerEvents(SharedPtr<ControllerAgent> a_controller) {
    
    EventsContainer container = a_controller->GetEventContainer();
    return std::count_if(container.begin(), container.end(), CheckEvent());
    //return 0;
}


//------------------------------ tests ----------------------------//

UNIT(thread_test) 
    //init test
    const size_t eventQueueSize = 20;
    Server server(eventQueueSize);
    Hub hub(server);

    //load and create agents
    Type fireType("fire");
    Location controllerLocation("2", "1");
    SharedPtr<ControllerAgent> fireController = MakeController(fireType, controllerLocation, "1");

    Location sensorLocation("2", "1");
    SharedPtr<SensorAgent> fireSensor = makeSensor(server.GetEventBus(), "2", fireType ,sensorLocation);

    server.AddAgent(fireController);

    //send events
    size_t numOfFireEvents = 1;
    fireSensor->StartSensor(numOfFireEvents);

    sleep(1);
    hub.ShutDownHub();
    ASSERT_EQUAL(fireController->GetNumOfEventsRecived(), numOfFireEvents);
    ASSERT_THAT(1);
END_UNIT

UNIT(controller_1_sensors_1) 
    //init test
    const size_t eventQueueSize = 20;
    Server server(eventQueueSize);
    Hub hub(server);
    
    //load and create agents
    Type fireType("fire");
    Location controllerLocation("*", "1");
    SharedPtr<ControllerAgent> fireController = MakeController(fireType, controllerLocation, "1");

    Location sensorLocation("2", "1");
    SharedPtr<SensorAgent> fireSensor = makeSensor(server.GetEventBus(), "1", fireType ,sensorLocation);

    server.AddAgent(fireController);

    //send events
    size_t numOfFireEvents = 1000;
    fireSensor->StartSensor(numOfFireEvents);
    sleep(1);
    hub.ShutDownHub();

    //check results
    ASSERT_EQUAL(fireController->GetNumOfEventsRecived(), numOfFireEvents);
END_UNIT


UNIT(controller_2_sensors_2) 
    //init test
    const size_t eventQueueSize = 20;
    Server server(eventQueueSize);
    Hub hub(server);
    
    //load and create agents
    Type fireType("fire");
    Type lightType("light");
    Location controllerLocation("*", "1");
    SharedPtr<ControllerAgent> fireController = MakeController(fireType, controllerLocation, "1");
    SharedPtr<ControllerAgent> lightController = MakeController(lightType, controllerLocation, "2");
    

    Location sensorFireLocation("8", "1");
    SharedPtr<SensorAgent> fireSensor = makeSensor(server.GetEventBus(), "1", fireType ,sensorFireLocation);
    Location sensorLightLocation("5", "1");
    SharedPtr<SensorAgent> lightSensor = makeSensor(server.GetEventBus(), "2", lightType ,sensorLightLocation);

    server.AddAgent(fireController);
    server.AddAgent(lightController);

    //send events
    size_t numOfFireEvents = 1;
    size_t numOfLightEvents = 1;
    fireSensor->StartSensor(numOfFireEvents);
    lightSensor->StartSensor(numOfLightEvents);

    sleep(1);
    hub.ShutDownHub();
    //check results
    ASSERT_EQUAL(fireController->GetNumOfEventsRecived(), numOfFireEvents);
    ASSERT_EQUAL(lightController->GetNumOfEventsRecived(), numOfLightEvents);
END_UNIT

UNIT(controller_2_sensors_2_1_same_type) 
    //init test
    const size_t eventQueueSize = 20;
    Server server(eventQueueSize);
    Hub hub(server);
    
    //load and create agents
    Type fireType("fire");
    Type lightType("light");
    Location controllerLocation("*", "1");
    SharedPtr<ControllerAgent> fireController = MakeController(fireType, controllerLocation, "1");
    SharedPtr<ControllerAgent> lightController = MakeController(lightType, controllerLocation, "2");
    
    Location sensorFireLocation("22", "1");
    SharedPtr<SensorAgent> fireSensor = makeSensor(server.GetEventBus(), "1", fireType ,sensorFireLocation);
    Location sensorLightLocation("58", "1");
    SharedPtr<SensorAgent> lightSensor = makeSensor(server.GetEventBus(), "2", lightType ,sensorLightLocation);

    Location seconLocation("*", "1");
    fireController->AddTypeToRegister(lightType, seconLocation);
    server.AddAgent(fireController);
    server.AddAgent(lightController);

    //send events
    size_t numOfFireEvents = 1000;
    size_t numOfLightEvents = 500;
    fireSensor->StartSensor(numOfFireEvents);
    lightSensor->StartSensor(numOfLightEvents);

    sleep(1);
    hub.ShutDownHub();

    //check results
    ASSERT_EQUAL(fireController->GetNumOfEventsRecived(), numOfFireEvents);
    ASSERT_EQUAL(lightController->GetNumOfEventsRecived(), numOfLightEvents);
END_UNIT

UNIT(controller_n_sensors_n) 
    //init test
    const size_t eventQueueSize = 20;
    Server server(eventQueueSize);
    Hub hub(server);
    
    //make controller and sensors
    std::vector<SharedPtr<ControllerAgent> > controllers = MakeControllers();
    std::vector<SharedPtr<SensorAgent> > sensors = MakeSensors(server.GetEventBus());
    SharedPtr<ControllerAgent> wildCard = MakeWildCard();

    AddAgentsToHub(server, controllers);  
    server.AddAgent(wildCard);

    //send events
    size_t numOfEvents = 100;
    size_t numOfSensors = 9;
    SendEvents(sensors, numOfEvents);

    //check results
    sleep(1);
    hub.ShutDownHub();

    int sum = SumReciveEvents(controllers);
    int equal = numOfEvents * numOfSensors;
    ASSERT_EQUAL(wildCard->GetNumOfEventsRecived(), numOfEvents * numOfSensors);
    ASSERT_EQUAL(sum , equal);
    ASSERT_THAT(1);
END_UNIT

UNIT(event_order_test)
    //init test
    const size_t eventQueueSize = 20;
    Server server(eventQueueSize);
    Hub hub(server);

    //make controller and sensors
    std::vector<SharedPtr<ControllerAgent> > controllers = MakeControllers();
    std::vector<SharedPtr<SensorAgent> > sensors = MakeSensors(server.GetEventBus());
    SharedPtr<ControllerAgent> wildCard = MakeWildCard();

    AddAgentsToHub(server, controllers);  
    server.AddAgent(wildCard);

    //send events
    size_t numOfEvents = 1000;
    size_t numOfSensors = 9;
    //size_t numOfControllers = 12;
    SendEvents(sensors, numOfEvents);

    sleep(1);
    hub.ShutDownHub();
    //check results

    ControllersVector::iterator begin = controllers.begin();
    ControllersVector::iterator end = controllers.end();
    int sumCheckedEvent = 0;
    while (begin != end) {
        sumCheckedEvent += CheckControllerEvents(*begin);
        ++begin;
    }

    int sum = SumReciveEvents(controllers);
    ASSERT_EQUAL(wildCard->GetNumOfEventsRecived(), numOfEvents * numOfSensors);
    ASSERT_EQUAL(sum , sumCheckedEvent);

END_UNIT

TEST_SUITE(mvpTest)
    TEST(thread_test) 
    TEST(controller_1_sensors_1)
    TEST(controller_2_sensors_2) 
    TEST(controller_2_sensors_2_1_same_type) 
    TEST(controller_n_sensors_n)
    TEST(event_order_test)
END_SUITE 