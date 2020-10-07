#ifndef DISPATHER_POOL_HPP
#define DISPATHER_POOL_HPP
#include "dispatcher.hpp"
#include "thread_pool.hpp"
#include "WaitableBoundedQueue.hpp"

namespace smartHome {

typedef WaitableBoundedQueue<Dispather> dispatherContainer;

class DisptherPool {
public:
    DisptherPool(size_t a_size);
    //~DisptherPool() = default;

    void AddDispathTask(SubcriberList a_list, SharedPtr<Event> a_event);
private:
    dispatherContainer m_dispathers;
    TreadPool m_threadPool;
    SharedPtr<Runnable> m_dispathRun;
};

}//smartHome

#endif // DISPATHER_POOL_HPP