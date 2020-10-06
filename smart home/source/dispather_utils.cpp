#include "dispaher_utils.hpp"
#include "controller_agent.hpp"
#include <iostream>
namespace smartHome {

DispathRunnable::DispathRunnable(ControllerList& a_list, SharedPtr<Event> a_event)
    : m_list(a_list)
    , m_event(a_event)
{
}

DispathRunnable::~DispathRunnable()
{
}

void DispathRunnable::Run() {
    SubcriberListItr begin = m_list.BeginItr();
    SubcriberListItr end = m_list.EndItr();
    while (begin != end) {
        begin->get()->HandleEvent(m_event);
        ++begin;
    }
}

}//smartHomen

