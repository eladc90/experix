#include "key_generator.hpp"
#include <algorithm>

namespace smartHome {

EventKeyGenerator::
EventKeyGenerator(SharedPtr<Event> a_event)
    : m_keys(InsertKeys(a_event))
{
}

std::string EventKeyGenerator::GenerateOnlyKey(SharedPtr<Event> a_even) {
    std::string rtString = a_even->GetType().GetType();
    rtString += a_even->GetLocation().GetRoom();
    rtString += a_even->GetLocation().GetFloor();
    return rtString;
}

std::string EventKeyGenerator::GenerateWholeFloorKey(SharedPtr<Event> a_even) {
    std::string rtString = a_even->GetType().GetType();
    rtString += "*";
    rtString += a_even->GetLocation().GetFloor();
    return rtString;
}

std::string EventKeyGenerator::GenerateWholeBuildingKey(SharedPtr<Event> a_even) {
    std::string rtString = a_even->GetType().GetType();
    rtString += "*";
    rtString += "*";
    return rtString;
}

std::string EventKeyGenerator::GenerateWholeSystemKey(SharedPtr<Event> a_even) {
    std::string rtString = "*";
    rtString += "*";
    rtString += "*";
    return rtString;
}

std::string EventKeyGenerator::GenerateRoomEveryFloorKey(SharedPtr<Event> a_even) {
    std::string rtString = a_even->GetType().GetType();
    rtString += a_even->GetLocation().GetRoom();
    rtString += "*";
    return rtString;
}

std::string EventKeyGenerator::GenerateRoomEveryTypeAndFloorKey(SharedPtr<Event> a_even) {
    std::string rtString = "*";
    rtString += a_even->GetLocation().GetRoom();
    rtString += "*";
    return rtString;
}

std::string EventKeyGenerator::GenerateEveryTypeRoomAndFloor(SharedPtr<Event> a_even) {
    std::string rtString = "*";
    rtString += a_even->GetLocation().GetRoom();
    rtString += a_even->GetLocation().GetFloor();
    return rtString;
}

std::string EventKeyGenerator::GenerateEveryTypeAndRoomInFloor(SharedPtr<Event> a_even) {
    std::string rtString = "*";
    rtString += "*";
    rtString += a_even->GetLocation().GetFloor();
    return rtString;
}

keys EventKeyGenerator::InsertKeys(SharedPtr<Event> a_event) {
    keys keysCont;
    keysCont.push_back(GenerateOnlyKey(a_event));
    keysCont.push_back(GenerateWholeFloorKey(a_event));
    keysCont.push_back(GenerateWholeBuildingKey(a_event));
    keysCont.push_back(GenerateWholeSystemKey(a_event));

    keysCont.push_back(GenerateRoomEveryFloorKey(a_event));
    keysCont.push_back(GenerateRoomEveryTypeAndFloorKey(a_event));
    keysCont.push_back(GenerateEveryTypeRoomAndFloor (a_event));
    keysCont.push_back(GenerateEveryTypeAndRoomInFloor (a_event));
    return keysCont;
}

keys EventKeyGenerator::GetKeys() {
    return m_keys;
}

}//smartHome