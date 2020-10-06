#include "event_bus.hpp"

namespace smartHome {

EventBus::EventBus(size_t a_size)
    : m_container(a_size)
{
}

EventBus::~EventBus()
{
}

void EventBus::PushEvent(SharedPtr<Event> a_event) {
    m_container.Enqueue(a_event);
}

void EventBus::PullEvent(SharedPtr<Event>& a_event) {
    m_container.Dequeue(a_event);
}

size_t EventBus::Size() const NOEXCEPTIONS{
    return m_container.Size();
}

}//smartHome