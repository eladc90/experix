#include <iostream>
#include "hub.hpp"
#include "hub_utils.hpp"

namespace smartHome {


Hub::Hub(Server& a_server) 
    : m_puller(a_server.GetEventBus())
    , m_pusher(a_server.GetEventBus())
    , m_distList(a_server.GetDlist())
    , m_IsShutingDown(false)
    , m_runnableHub(new HubRunnable(*this))
    , m_hubThread(*m_runnableHub)
    , m_server(a_server)
{   
}

Hub::~Hub() 
{
    m_hubThread.Join();
}

void Hub::DisributeEvent(SharedPtr<Event> a_event) {
    try {
        ListToDispath controllerList = m_distList.GetMailListByEvent(a_event);
        m_server.AddDispathTask(controllerList, a_event);
    }
    catch (std::exception ex) {
        std::cout << "this is not valid list" << std::endl;
    }
}

void Hub::Distribute() {
    SharedPtr<Event> event; 
    while (m_puller->Size() != 0 && !m_IsShutingDown) {
        m_puller->PullEvent(event);
        DisributeEvent(event);
    }
}

bool Hub::IsShutingDown() {
    return m_IsShutingDown;
}

void Hub::ShutDownHub() {
    m_IsShutingDown = true;
    ShutDown();
}

void Hub::ShutDown() {
    //m_threadPool.ShutDownDispath();
}

/* void Hub::AddAgent(SharedPtr<IAgent> a_agent) {
    a_agent->Connent(m_distList, m_pusher);
} */

}//smartHome