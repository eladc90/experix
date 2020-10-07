#include <iostream>
#include <string>
#include "mu_test.h"
#include "hub.hpp"
#include "event_bus.hpp"
#include "event_pusher.hpp"
#include "event_puller.hpp"

using namespace smartHome;


class ControllerInfo {
public:
    ControllerInfo(std::string a_type, std::string a_id, std::string a_room, std::string a_floor)
        : m_type(a_type)
        , m_id(a_id)
        , m_room(a_room)
        , m_floor(a_floor) {}
    std::string GetId() { return m_id; }
    std::string GetType() { return m_type; }
    std::string GetRoom() { return m_room; }
    std::string GetFloor() { return m_floor; }
private:
    std::string m_type;
    std::string m_id;
    std::string m_room;
    std::string m_floor;


};

//-------------------- aid  functions ------------------------//TODO

SharedPtr<ControllerAgent> MakeController(ControllerInfo a_info) {
    return SharedPtr<ControllerAgent>( new ControllerAgent(a_info.GetId(), a_info.GetType(),
                                        "log", a_info.GetRoom(), a_info.GetFloor()));     
}

//--------------------- tests -----------------------------//

typedef std::string ControllerType;
typedef std::string ControllerId;
typedef std::string ControllerRoom;
typedef std::string ControllerFloor;

UNIT(regist_test)
    //init hub
    const size_t eventQueueSize = 20;
    EventBus eventBus(eventQueueSize);
    EventPusher pusher(eventBus);
    EventPuller puller(eventBus);
    Hub hub(eventQueueSize, puller);

    //init controller
    
    ControllerInfo info("fire", "1", "1", "1");
    SharedPtr<ControllerAgent> controller = MakeController(info);

    hub.AddController(controller);
    hub.ShutDownHub();
    ASSERT_THAT(1);

END_UNIT

TEST_SUITE(regist)
    TEST(regist_test)
END_SUITE 