#ifndef _THREAD_POOL_HPP_
#define _THREAD_POOL_HPP_

#include <vector>
#include  <cstddef>
#include <sys/sysinfo.h>
#include "common_utils.hpp"
#include "common.hpp"
#include "runnable.hpp"
#include "thread.hpp"
#include "WaitableBoundedQueue.hpp"
#include "task_consumer.hpp"
#include "mutex.hpp"
#include "thread_container.hpp"

namespace smartHome {

class TreadPool : private Uncopyable {

//! @brief create a safe pool of threads

    static size_t DefaultSize() { return get_nprocs() / 2; }

public:
    //!@brief Ctor of the thread pool
    //!@param[in] a_capacity - the max number of tasks
    //!@param[in] a_numOfThread - number of threads
    explicit TreadPool(size_t a_capacity, size_t a_numOfThread = DefaultSize());

    //!@brief Dtor of the thread pool
    ~TreadPool();
    
    //!@brief add task t the container
    //!@param[in] a_task - shared pointer to the task
    void AddTask(SharedPtr<Runnable> const& a_task);

    //!@brief add threads to the thread container
    //!@param[in] a_numOfThreads - number of thread to add. default = 1
    void AddThread(size_t a_numOfThreads = 1);

    //!@brief remove threads from the container
    //!@param[in] a_numOfThreads - number of thread to remove. default = 1
    void RemoveThread(size_t a_numOfThread = 1);

    //!@brief shut down the thread pool
    //!@param[in] a_timeInMicroSec - time in milisec to shut down the pool
    // return false if the threads didnt finish before the time has pass
    bool ShutDown(size_t a_timeInMicroSec = 0);

    //!@brief imediatly shut down the pool
    //!@param[in] a_timeInMicroSec - time in milisec to shut down the pool
    void ShutDownImediate();

    //!@brief make join to all the threads in the container
    void JoinThreads();
    
private:
    timespec InitTimeSpec();

private:
    WaitableBoundedQueue<SharedPtr<Runnable> > m_tasks;
    SharedPtr<Runnable> m_taskConsumer;
    ThreadContainer m_threads; 
    Mutex m_mutex;

};


}//smartHome


#endif // !_THREAD_POOL_HPP_