#include "door_controller_2_floor.hpp"
#include "sprinkler_controller.hpp"
#include "fire_sensor.hpp"
#include "common.hpp"
#include "i_agent.hpp"

namespace smartHome{


extern "C" {
    SharedPtr<IAgent> CreatingDoor(std::string a_room, std::string a_floor) {
        return  SharedPtr<IAgent>(new DoorController(a_room, a_floor));
    }
}

extern "C" {
    SharedPtr<IAgent> CreatingSprinkel(std::string a_room, std::string a_floor) {
        return SharedPtr<IAgent>(new Sprinkler(a_room, a_floor));
    }
    
}

extern "C" {
    size_t numOfEventt = 10;
    SharedPtr<IAgent> CreatingFireSensor(std::string a_room, std::string a_floor) {
        return SharedPtr<IAgent>(new FireSensor(a_room, a_floor, numOfEventt));
    }
    
}
}//smartHome