#ifndef DISPATHER_UTILS_HPP
#define DISPATHER_UTILS_HPP
#include <vector>
#include "runnable.hpp"
#include "WaitableBoundedQueue.hpp"
#include "common.hpp"
#include "event.hpp"
#include "distributaion_list.hpp"
#include "I_event_handler.hpp"
#include "subcriber_list.hpp"

namespace smartHome {

typedef WaitableBoundedQueue<SharedPtr<Event> > EventContainer;
typedef SubcriberList ControllerList;

class DispathRunnable : public Runnable {
public:
    DispathRunnable(ControllerList& a_list, SharedPtr<Event> a_event);
    ~DispathRunnable();

    void Run();

private:
    ControllerList& m_list;
    SharedPtr<Event> m_event;
};

}//smartHome

#endif // DISPATHER_UTILS_HPP