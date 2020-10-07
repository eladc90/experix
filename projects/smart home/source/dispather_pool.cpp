#include "dispather_pool.hpp"
#include "dispath_runnable.hpp"
#include "dispatcher.hpp"

namespace smartHome {

DisptherPool::DisptherPool(size_t a_size)
    : m_dispathers(a_size)
    , m_threadPool(a_size)  
{
    while (a_size) {
        m_dispathers.Enqueue(Dispather());
        --a_size;
    }
}
    //DispthRun(Dispather& a_dispather, SubcriberList& a_subcribeList, SharedPtr<Event> a_event);

void DisptherPool::AddDispathTask(SubcriberList a_list, SharedPtr<Event> a_event) {
    Dispather dispath;
    m_dispathers.Dequeue(dispath);
    SharedPtr<Runnable> task(new DispthRun(dispath, a_list, a_event));
    m_threadPool.AddTask(task);
}

}//smartHome