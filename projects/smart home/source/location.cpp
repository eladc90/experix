#include "location.hpp"

namespace smartHome {

Location::Location(std::string a_room, std::string a_floor) 
    : m_room(a_room)
    , m_floor(a_floor)
{
}

Location::~Location()
{
}


std::string Location::GetFloor() {
    return m_floor;
}

std::string Location::GetRoom() {
    return m_room;
}

}//smartHome