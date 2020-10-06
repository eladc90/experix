#ifndef I_EVENT_HANDLER_HPP
#define I_EVENT_HANDLER_HPP
#include "event.hpp"

namespace smartHome {

class IEventHandler {
public:
    IEventHandler() {}
    ~IEventHandler() {}

    virtual void HandleEvent(SharedPtr<Event> a_event) = 0;
private:

};

}//smartHome

#endif // I_EVENT_HANDLER_HPP