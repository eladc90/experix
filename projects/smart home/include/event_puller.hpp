#ifndef EVENT_PULLER_HPP
#define EVENT_PULLER_HPP

#include <tr1/memory>
#include "WaitableBoundedQueue.hpp"
#include "event.hpp"

#define SharedPtr std::tr1::shared_ptr

namespace smartHome {

class EventPuller{

public:
    EventPuller() {}
    //~EventPuller() = default;

    virtual void PullEvent(SharedPtr<Event>& a_event) = 0;
    virtual size_t Size() const NOEXCEPTIONS = 0;
private:
    

};

}// smartHome

#endif // !EVENT_PUSHER_HPP