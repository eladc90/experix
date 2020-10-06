#ifndef EVENT_BUS_HPP
#define EVENT_BUS_HPP

#include "WaitableBoundedQueue.hpp"
#include "event.hpp"
#include "common.hpp"
#include "event_puller.hpp"
#include "event_pusher.hpp"

namespace smartHome {

typedef WaitableBoundedQueue<SharedPtr<Event> > eventsCont;

class EventBus : public EventPuller, public EventPusher {
public:
    EventBus(size_t a_size);
    ~EventBus();

    virtual void PushEvent(SharedPtr<Event> a_event);
    virtual void PullEvent(SharedPtr<Event>& a_event);
    virtual size_t Size() const NOEXCEPTIONS;
private:
    eventsCont m_container;
};

}//smartHome

#endif // EVENT_BUS_HPP