#ifndef _TASK_CONSUMER_HPP_
#define _TASK_CONSUMER_HPP_


#include "common.hpp"
#include "runnable.hpp"
#include "WaitableBoundedQueue.hpp"

namespace smartHome {

class TaskConsumer : public Runnable{
public:
    explicit TaskConsumer(WaitableBoundedQueue<SharedPtr<Runnable> >& a_queue);
    ~TaskConsumer();

    virtual void Run();

private:
    WaitableBoundedQueue<SharedPtr<Runnable> >& m_queue;
};

}//smartHome

#endif // _TASK_CONSUMER_HPP_ 