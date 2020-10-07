#ifndef COMMON_UTILS_HPP
#define COMMON_UTILS_HPP
#define NOEXCEPTIONS throw()

namespace smartHome {

class ConditionVar;
class Mutex;

class SignalGuard {
public:
    SignalGuard(ConditionVar& a_condVal);
    ~SignalGuard();
    void NotifyOne();
private:
    ConditionVar& m_condVar;
    bool m_notifyAllFlag;
};

class MutexGuard {
public:
    MutexGuard(Mutex& a_mutex);
    ~MutexGuard();
private:
    Mutex& m_mutex;
};

}// namespace smartHome

#endif // COMMON_UTILS_HPP
