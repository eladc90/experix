#include "Task.h"
#include "STS.h" 
#include "heap.h"
#include "vector.h" 
#include "timer.h" 
#include "Pqueue.h" 
#include "zlog.h" 
#include <stddef.h> /*size_t*/
#include <stdlib.h> /* malloc */

#define MAGIC_NUMBER 0XBADBABE
#define UN_MAGIC_NUMBER 0XFEEDFACE
#define INIT_NUM_OF_TASKS 10

/*======================================== static functions =====================================*/

static StatusScheduler CheckTaskParam(Scheduler *_Scheduler, TaskActionFunction _action, size_t _intervalTime);

/*===============================================================================================*/




struct Scheduler
{
    size_t m_magicNumber;
    Pqueue *m_tasksArr;
    size_t m_numOfTasks;
};


Scheduler* SchedulerCreate()
{
    Pqueue *Pqueue = NULL;
    Scheduler *sched = NULL;

    sched = (Scheduler *) malloc (sizeof(Scheduler));
    if (sched == NULL)
    {
        return NULL;
    }
    Pqueue = PqeueuCreate(TimeCompareLess);
    if (Pqueue == NULL)
    {
        free(sched);
        return NULL;
    }

    sched -> m_tasksArr = Pqueue;
    sched -> m_numOfTasks = 0;
    sched -> m_magicNumber = MAGIC_NUMBER;
    ZlogInit("logger.log");
    ZLOG(TRCAE, "schedule create");
    return sched;
}



void SchedulerDestroy (Scheduler* _Scheduler)
{
    if (_Scheduler -> m_magicNumber != MAGIC_NUMBER)
    {
        return;
    }
    _Scheduler -> m_magicNumber = UN_MAGIC_NUMBER;
    PqueueDesroy((_Scheduler -> m_tasksArr), DestoryElement);
    free(_Scheduler);
    ZLOG(TRCAE, "schedule destroy");
    return;
}

void DestoryElement(void *_element)
{
    TaskDestroy((Task *)_element);
    return;
}


StatusScheduler SchedulerAddTask (Scheduler *_Scheduler, void *_context, TaskActionFunction _action, size_t _intervalTime)
{
    Task *newTask;
    StatusScheduler status;
    status = CheckTaskParam(_Scheduler, _action, _intervalTime);
    if (status != SCHEDULER_OK)
    {
        return status;
    }
    newTask = TaskCreate(_action, _context, _intervalTime);
    if (newTask == NULL)
    {
        return SCHEDULER_NULL_ERR;
    }
    status = PqueueInsert(_Scheduler -> m_tasksArr, newTask);
    if (status != SCHEDULER_OK)
    {
        return status;
    }
    _Scheduler -> m_numOfTasks++;
    ZLOG(TRCAE, "adding a task");
    return SCHEDULER_OK;
}   





int SchedulerRun (Scheduler *_Scheduler)
{
    size_t taskTime = 0;
    size_t updateTime = 0;
    size_t getTime = 0;
    size_t statusOfTask = 0;
    Task* task;

    initGlClock();
    while(_Scheduler -> m_numOfTasks != 0)
    {
        task = PqueueExtract(_Scheduler -> m_tasksArr);
        taskTime = GetNextRun(task);
        getTime = TimeSleep(taskTime);
        if (getTime > 0)
        {
            TimerWait(getTime);
        }

        statusOfTask = TaskRun(task);
        if (statusOfTask == 0)
        {
            TaskUpdate(task);
            PqueueInsert(_Scheduler -> m_tasksArr, task);
        }
        else
        {
            TaskDestroy(task);
            _Scheduler -> m_numOfTasks--;
        } 
    }
    return 0;
}


/*============================================ aux functions ===================================================*/



static StatusScheduler CheckTaskParam(Scheduler *_Scheduler, TaskActionFunction _action, size_t _intervalTime)
{
    if (_Scheduler == NULL)
    {
        return SCHEDULER_NULL_ERR;
    }
    if (_action == NULL || _intervalTime == 0)
    {
        return SCHEDULER_INVLID_INPUT;
    }
    return SCHEDULER_OK;
}
