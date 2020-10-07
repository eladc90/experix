#ifndef DISPATCHER_HPP
#define DISPATCHER_HPP
#include <vector>
#include "controller_agent.hpp"
#include "WaitableBoundedQueue.hpp"
#include "common.hpp"
#include "thread_pool.hpp"
#include "subcriber_list.hpp"

namespace smartHome{

typedef WaitableBoundedQueue<SharedPtr<Event> > EventContainer;
typedef SubcriberList ControllerList;

class Dispather {
public:
    Dispather(size_t a_size = 1);
    ~Dispather();

    void Dispath(ControllerList& a_list, SharedPtr<Event> a_event); // TODO

private:

};

}//smartHome
#endif //DISPATCHER_HPP