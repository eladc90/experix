#include <iostream>
#include "task_consumer.hpp"
#include "poision_apple.hpp"
#include "common.hpp"

namespace smartHome {

TaskConsumer::TaskConsumer(WaitableBoundedQueue<SharedPtr<Runnable> >& a_queue)
: m_queue(a_queue) {
}

TaskConsumer::~TaskConsumer() 
{
}

void TaskConsumer::Run(){
    while (true) {
        try{  
            
            SharedPtr<Runnable> runTask;
            m_queue.Dequeue(runTask);
            runTask->Run();
        }
        catch(const PoisionAppleException) {
            break;
        }
    }   
}

}//smartHome