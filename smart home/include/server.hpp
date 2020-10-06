#ifndef SERVER_HPP
#define SERVER_HPP
#include "event_bus.hpp"
#include "distributaion_list.hpp"
#include "distributer_pool.hpp"

namespace smartHome {

const size_t numOfThread = 8;

class Server {

typedef std::pair<SharedPtr<Event>, SubcriberList> queuePair;
typedef SharedPtr<WaitableBoundedQueue<queuePair> > DispatherList;
typedef std::vector<DispatherList> DispathersQueues;
typedef std::vector<SubcriberList> ListToDispath;

public:
    explicit Server(size_t a_size);
    ~Server();

    SharedPtr<EventBus> GetEventBus();
    DistributionList& GetDlist();
    void AddAgent(SharedPtr<IAgent> a_agent);
    void AddDispathTask(ListToDispath& a_list, SharedPtr<Event> a_event);
private:
    DispathersQueues InitQueues();
    void AddTasks();

private:
    SharedPtr<EventBus> m_eventBus;
    DistributionList m_distList;
    DistributerPool m_threadPool;
    DispathersQueues m_dispathersQueues;
};

}//smartHome

#endif // SERVER_HPP