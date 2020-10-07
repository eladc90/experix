#include "controller_container.hpp"
#include "common.hpp"
#include <iostream>

namespace smartHome {

ControllerContainer::ControllerContainer()
    :m_container()
{
}

ControllerContainer::~ControllerContainer()
{
}

void ControllerContainer::AddController(ControllerAgent& a_controller) {
    m_container.push_back(a_controller);
}

void ControllerContainer::NotifyEvent(SharedPtr<Event> a_event) {
    ControllerCont::iterator begin = m_container.begin();
    ControllerCont::iterator end = m_container.end();
    while (begin != end) {
        begin->HandleEvent(a_event);
        ++begin;
    }
}

}//smartHome