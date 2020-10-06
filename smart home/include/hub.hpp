#ifndef HUB_HPP
#define HUB_HPP
#include "uncopyable.hpp"
#include "distributaion_list.hpp"
#include "dispatcher.hpp"
#include "event_bus.hpp"
#include "subcriber_list.hpp"
#include "event_puller.hpp"
#include "distributer_pool.hpp"
#include "i_agent.hpp"
#include "event_pusher.hpp"
#include "server.hpp"

namespace smartHome {

//const size_t numOfThread = 8;

class Hub : private Uncopyable{

public:
    Hub(Server& a_server);
    ~Hub();

    void ShutDownHub();
    bool IsShutingDown();
    void Distribute();

private:
    void ShutDown();
    void DisributeEvent(SharedPtr<Event> a_event);
    void AddDispathTask(ListToDispath& a_list, SharedPtr<Event> a_event);
    void AddTasks();

private:
    SharedPtr<EventPuller> m_puller;
    SharedPtr<EventPusher> m_pusher;
    DistributionList& m_distList;
    bool m_IsShutingDown;
    SharedPtr<Runnable> m_runnableHub;
    Thread m_hubThread;
    Server& m_server;
};

}//smartHome

#endif // HUB_HPP