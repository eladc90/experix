#ifndef __STS_H__
#define __STS_H__


typedef struct Scheduler Scheduler;


typedef enum StatusScheduler
{
    SCHEDULER_OK,
    SCHEDULER_NULL_ERR,
    SCHEDULER_INVLID_INPUT
}StatusScheduler;

/** 
 * 
 * 
 * 
 *  @file  scheduler.h
 *  @brief create  and destroy container that hold the tasks.
 * add and remove of tasks from the container.
 */


/**
 * @brief Dynamically creates a new task object.
 * @param[in] _numOfTasks - the number of tasks created.
 * @return A pointer to the Scheduler created.
 * 
 * @warning If _numOfTasks equlal to  0 or the allocation fail the function return NULL.
 */
Scheduler* SchedulerCreate();

/**

 * @brief destroy the scheduler.
 * @param[in] _Scheduler - a pointer to the scheduler.
 * @return return status.
 * 
 * @warning If _Scheduler NULL the function return NULL.
 */
void SchedulerDestroy (Scheduler *_Scheduler);

/**

 * @brief add task to the sched.
 * @param[in] _Scheduler - a pointer to the scheduler.
 * @param[in] _action - the function of the task.
 * @param[in] _numOfRuns - How many times the function has to be executed.
 * @param[in] _timePass - How much mili seconds have to pass until the next execute.
 * @return return status.
 * 
 * @warning If _Scheduler NULL the function return NULL.
 */
StatusScheduler SchedulerAddTask (Scheduler *_Scheduler, void *_context, TaskActionFunction _action, size_t _intervalTime);

/**

 * @brief run the scheduel.
 * @param[in] _Scheduler - a pointer to the scheduler.
 * @return return status.
 * 
 * @warning If _Scheduler NULL the function return NULL.
 */
int SchedulerRun (Scheduler *_Scheduler);

/**

 * @brief destroy an element from the schedule.
 * @param[in] _element - a pointer to the element.
 * 
 * 
 * 
 */

void DestoryElement(void *_element);

 #endif /*__STS_H__*/