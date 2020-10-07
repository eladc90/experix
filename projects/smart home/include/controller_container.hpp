#ifndef CONTROLLER_CONTAINER_HPP
#define CONTROLLER_CONTAINER_HPP
#include <list>
#include "controller_agent.hpp"
#include "event.hpp"
#include "common.hpp"

namespace smartHome{

typedef std::list<ControllerAgent> ControllerCont;

class ControllerContainer {
public:
    ControllerContainer();
    ~ControllerContainer();

    void AddController(ControllerAgent& a_controller);
    void NotifyEvent(SharedPtr<Event> a_event);
private:
    ControllerCont m_container;

};

}//smartHome

#endif //  CONTROLLER_CONTAINER_HPP