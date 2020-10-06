#include "server.hpp"

namespace smartHome {

Server::Server(size_t a_size)
    : m_eventBus(new EventBus(a_size))
    , m_distList()
    , m_threadPool(a_size, numOfThread) 
    , m_dispathersQueues(InitQueues())
{
    AddTasks();
}

Server::~Server() {
    m_threadPool.ShutDownDispath();
}

SharedPtr<EventBus> Server::GetEventBus() {
    return m_eventBus;
}

DistributionList& Server::GetDlist() {
    return m_distList;
}

Server::DispathersQueues Server::InitQueues() {
    DispathersQueues queues;
    for (size_t i = 0; i < numOfThread; ++i) {
        SharedPtr<WaitableBoundedQueue<queuePair> > newQueue(new WaitableBoundedQueue<queuePair>(numOfThread));
        queues.push_back(newQueue);
    } 
    return queues; 
}

void Server::AddTasks() {
    for (size_t i = 0; i < numOfThread; ++i) {
        m_threadPool.AddDispatherTask(m_dispathersQueues[i]);
    } 
}


void Server::AddDispathTask(ListToDispath& a_list, SharedPtr<Event> a_event) {
    ListToDispath::iterator begin = a_list.begin();
    ListToDispath::iterator end = a_list.end();
    int i = 0;
    while (begin != end) { 
        m_dispathersQueues.at(i)->Enqueue(std::make_pair(a_event ,*begin));
        ++begin;
        ++i;
    }
}

void Server::AddAgent(SharedPtr<IAgent> a_agent) {
    a_agent->Connent(m_distList, m_eventBus);
}

}//smartHome