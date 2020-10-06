#include "distributer_pool_utils.hpp"
#include "distributer_pool.hpp"

namespace smartHome {

DispatherRunnable::DispatherRunnable(EventQueue a_queue, DistributerPool& a_dPool)
    : m_eventQueue(a_queue)
    , m_dPool(a_dPool)
    , m_dispather()
    , m_mutexRunnable()
{
}

DispatherRunnable::~DispatherRunnable() 
{
}

void DispatherRunnable::Run() {

    ReadyToWorkPredicte readyPredicate(m_dPool);
    DistributPredicte workDonePredicate(m_dPool);
    while (!m_dPool.IsShutDown()) {

        m_dPool.TestAndSetReadyToWorkingNum();

        m_mutexRunnable.Lock();
        m_dPool.GetCondVar().Wait(m_mutexRunnable , &readyPredicate);
        m_mutexRunnable.UnLock();

        if (m_eventQueue->Size() != 0) {
            queuePair eventAndList;
            m_eventQueue->Dequeue(eventAndList);
            m_dispather.Dispath(eventAndList.second, eventAndList.first);
        }

        m_dPool.TestAndSetWorkingNum();
        m_mutexRunnable.Lock();
        m_dPool.GetCondVar().Wait(m_mutexRunnable, &workDonePredicate);
        m_mutexRunnable.UnLock(); 

    } 
}


}//smartHome
