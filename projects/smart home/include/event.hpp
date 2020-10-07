#ifndef EVENT_HPP
#define EVENT_HPP

#include <string>
#include "location.hpp"
#include "type.hpp"
#include "payload.hpp"
#include "id.hpp"
#include "common_utils.hpp"
#include <iostream>

namespace smartHome{

class Event {
public:

    Event(ID& a_id, Type& a_type, Location& a_location);
    ~Event();
    Event(const Event& a_other);
    Event& operator=(const Event& a_other);

    const ID& GetId() const NOEXCEPTIONS;
    const Type& GetType() const NOEXCEPTIONS;
    Location GetLocation() NOEXCEPTIONS;
    void Print() { std::cout << "the id is: " <<m_id.GetId() << std::endl; }
private:
    ID m_id;
    Type m_type;
    Location m_location;

};

}// smartHome

#endif // EVENT_HPP