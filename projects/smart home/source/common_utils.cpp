#include "common_utils.hpp"
#include "mutex.hpp"
#include "condition_var.hpp"

namespace smartHome {

SignalGuard::SignalGuard(ConditionVar& a_condVar)
    : m_condVar(a_condVar)
    , m_notifyAllFlag(true) 
{
}

SignalGuard::~SignalGuard() {
    if (m_notifyAllFlag) {
        m_condVar.NotifyAll();
    }
}

void SignalGuard::NotifyOne() {
    m_condVar.SignalOne();
    m_notifyAllFlag = false;
}

MutexGuard::MutexGuard(Mutex& a_mutex) 
    :m_mutex(a_mutex) {
        m_mutex.Lock();   
} 

MutexGuard::~MutexGuard() {
        m_mutex.UnLock();
}

}// namespace smartHome