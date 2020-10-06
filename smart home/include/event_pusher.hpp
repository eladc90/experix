#ifndef EVENT_PUSHER_HPP
#define EVENT_PUSHER_HPP

#include <tr1/memory>
#include "WaitableBoundedQueue.hpp"
#include "event.hpp"

#define SharedPtr std::tr1::shared_ptr

namespace smartHome {

class EventPusher{

public:
    EventPusher() {}
    //~EventPusher()  = default;   

    virtual void PushEvent(SharedPtr<Event> a_event) = 0;
    
private:

};

}// smartHome

#endif // !EVENT_PUSHER_HPP