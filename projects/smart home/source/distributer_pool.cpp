#include "distributer_pool.hpp"
#include "distributer_pool_utils.hpp"

namespace smartHome {

DistributerPool::DistributerPool(size_t a_capacity, size_t a_numOfThreads)
    : m_threadPool(a_capacity, a_numOfThreads)   
    , m_isShutDown(false) 
    , m_readyToWork(false)
    , m_finishToWork(false)
    , m_readyMutex()
    , m_workinDoneMutex()
    , m_workingThreadNum(0)
    , m_doneWorking(numOfThreads)
    , m_condVar()
{
}

DistributerPool::~DistributerPool() {
    m_isShutDown = true;
    m_condVar.NotifyAll();
    m_threadPool.ShutDown();
}

void DistributerPool::AddDispatherTask(EventQueue a_queue) {
    SharedPtr<Runnable> dispathRunnable(new DispatherRunnable(a_queue, *this));
    m_threadPool.AddTask(dispathRunnable);
}

bool DistributerPool::ShutDownDispath() {
    MutexGuard mutexGuard(m_readyMutex);
    {
        m_isShutDown = true;
        m_workingThreadNum = 0;
        m_condVar.NotifyAll();
        return true;//TODO
    }
}

ConditionVar& DistributerPool::GetCondVar() {
    return m_condVar;
}

bool DistributerPool::IsShutDown() {
    MutexGuard mutexGuard(m_readyMutex);
    if (m_isShutDown == 1) {
        return true;
    }
    return false;
}

Mutex& DistributerPool::GetMutex() {
    return m_readyMutex;
}

size_t& DistributerPool::GetNumOfWorking() {
    MutexGuard mutexGuard(m_readyMutex);
    return m_workingThreadNum;
}

void DistributerPool::TestAndSetWorkingNum() {
    MutexGuard mutexGuard(m_workinDoneMutex);
    {   
        if (--m_doneWorking == 0) {
            m_readyToWork = false;
            m_finishToWork = true;
            m_condVar.NotifyAll();
            m_doneWorking = numOfThreads;
        }
    }
}

void DistributerPool::TestAndSetReadyToWorkingNum() {
    MutexGuard mutexGuard(m_readyMutex);
    {
        if (++m_workingThreadNum == numOfThreads) {
            m_readyToWork = true;
            m_condVar.NotifyAll();
            m_workingThreadNum = 0;
        }
    }
}

bool DistributerPool::GetIfReadyToWork() {
    MutexGuard mutexGuard(m_readyMutex);
    if (m_isShutDown == 1) {
        return true;
    }
    return m_readyToWork;
}

bool DistributerPool::GetIfFinishToWork() {
    MutexGuard mutexGuard(m_workinDoneMutex);
    if (m_isShutDown == 1) {
        return true;
    }
    return m_finishToWork;
}

}//smartHome
