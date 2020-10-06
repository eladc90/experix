#ifndef KEY_GENERATOR_HPP
#define KEY_GENERATOR_HPP
#include <string>
#include <vector>
#include "location.hpp"
#include "type.hpp"
#include "event.hpp"
#include "common.hpp"

namespace smartHome {

typedef std::vector<std::string> keys;

class EventKeyGenerator {
public:
    EventKeyGenerator(SharedPtr<Event> a_event);
    //~EventKeyGenerator() = default;

    void GenerateKeysByEvent(SharedPtr<Event> a_event);

    keys GetKeys();

private:
    std::string GenerateWholeBuildingKey(SharedPtr<Event> a_even);//TODO
    std::string GenerateOnlyKey(SharedPtr<Event> a_even);
    std::string GenerateWholeFloorKey(SharedPtr<Event> a_even);
    std::string GenerateWholeSystemKey(SharedPtr<Event> a_even);
    std::string GenerateRoomEveryFloorKey(SharedPtr<Event> a_even);
    std::string GenerateRoomEveryTypeAndFloorKey(SharedPtr<Event> a_even);
    std::string GenerateEveryTypeRoomAndFloor(SharedPtr<Event> a_even);
    std::string GenerateEveryTypeAndRoomInFloor(SharedPtr<Event> a_even);
    keys InsertKeys(SharedPtr<Event> a_event);
private:

    keys m_keys;

};

}//smartHome

#endif // !KEY_GENERATOR_HPP