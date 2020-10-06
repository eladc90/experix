#ifndef DISTIBUTER_POOL_HPP
#define DISTIBUTER_POOL_HPP

#include "thread_pool.hpp"
#include "event.hpp"
#include "subcriber_list.hpp"
#include "mutex.hpp"
#include "distributer_pool_utils.hpp"

namespace smartHome {

typedef std::pair<SharedPtr<Event>, SubcriberList> queuePair;
typedef SharedPtr<WaitableBoundedQueue<queuePair> > EventQueue;

class DistributerPool {
public:
    explicit DistributerPool(size_t a_capacity, size_t a_numOfThreads);
    ~DistributerPool();

    void AddDispatherTask(EventQueue a_queue);
    bool ShutDownDispath();
    ConditionVar& GetCondVar();
    bool IsShutDown();
    Mutex& GetMutex();
    bool GetIfReadyToWork();
    void TestAndSetWorkingNum();
    void TestAndSetReadyToWorkingNum();
    size_t& GetNumOfWorking();
    bool GetIfFinishToWork();

private:


private:    
    TreadPool m_threadPool;
    bool m_isShutDown;
    bool m_readyToWork;
    bool m_finishToWork;
    Mutex m_readyMutex;
    Mutex m_workinDoneMutex;
    size_t m_workingThreadNum;
    size_t m_doneWorking;
    ConditionVar m_condVar;
};

}//smartHome

#endif // DISTIBUTER_POOL_HPP