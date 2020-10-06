#ifndef SENSOR_UTILS_HPP
#define SENSOR_UTILS_HPP

#include "runnable.hpp"
#include "sensor_agent.hpp"

namespace smartHome {

class SensorRunnable : public Runnable {
public:
    SensorRunnable(SharedPtr<EventPusher> a_eventPusher,  SharedPtr<Event> a_event, size_t a_numofEvents);
    ~SensorRunnable();

    virtual void Run();
private:
    SharedPtr<EventPusher> m_pusher;
    SharedPtr<Event> m_event;
    size_t m_numOfEvents;
};

}//smartHome

#endif //SENSOR_UTILS_HPP