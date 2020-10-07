#ifndef LOCATION_HPP
#define LOCATION_HPP
#include <string>

namespace smartHome{

class Location {
public:
    Location(std::string a_room, std::string a_floor);
    ~Location();
    std::string GetFloor();
    std::string GetRoom();

private:
    std::string m_room;
    std::string m_floor;
};

}// smartHome

#endif // LOCATION_HPP