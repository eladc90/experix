#ifndef ROOM_AND_FLOOR_LOC_HPP
#define ROOM_AND_FLOOR_LOC_HPP

#include "location.hpp"

namespace smartHome{

class RoomAndFloor : public Location {
public:
    RoomAndFloor(unsigned int a_roomNum, unsigned int a_floorNum);
    ~RoomAndFloor() {}
    
private:
    unsigned int m_roomNum;
    unsigned int m_floorNum;
};

}// smartHome

#endif // ROOM_AND_FLOOR_LOC_HPP