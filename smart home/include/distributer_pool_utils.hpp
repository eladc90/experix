#ifndef DISTRIBUTER_POOL_UTILS_HPP
#define DISTRIBUTER_POOL_UTILS_HPP
#include "runnable.hpp"
#include "subcriber_list.hpp"
#include "common.hpp"
#include "event.hpp"
#include "WaitableBoundedQueue.hpp"
#include "dispatcher.hpp"
#include "condition_var.hpp"

namespace smartHome {

class DistributerPool;
class DistributPredicte;
const size_t numOfThreads = 8;

class DispatherRunnable : public Runnable{

typedef std::pair<SharedPtr<Event>, SubcriberList> queuePair;
typedef SharedPtr<WaitableBoundedQueue<queuePair> > EventQueue;
public:
    DispatherRunnable(EventQueue a_queue, DistributerPool& a_dPool);
    ~DispatherRunnable();

    virtual void Run();
private:
    EventQueue m_eventQueue;
    DistributerPool& m_dPool;
    Dispather m_dispather;
    Mutex m_mutexRunnable;
};


class DistributPredicte {
public:
    DistributPredicte(DistributerPool& a_distPool);
    ~DistributPredicte();
    bool operator()();
private:
    DistributerPool& m_distPool;

};

class ReadyToWorkPredicte {
public:
    ReadyToWorkPredicte(DistributerPool& a_distPool);
    ~ReadyToWorkPredicte();
    bool operator()();
private:
    DistributerPool& m_distPool;
    

};

}//smartHome

#endif // DISTRIBUTER_POOL_UTILS_HPP