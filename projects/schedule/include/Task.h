#ifndef __TASK_H__
#define __TASK_H__

#include <stddef.h> /*size_t*/

/** 
 *  @file  Task.h
 *  @brief Creates a task that holds a pointer to a function
 *  and can execute it.
 *  how many times it has to run and the 
 */

typedef struct Task Task;

/**
 * @brief A pointer to the function the task holds and can execute.
 * @param[in] _context - User's context for the function.
 */
typedef int (*TaskActionFunction)(void* _context);



/**
* @brief Dynamically creates a new task object.
* @param[in] _action - A pointer to the function the task will run.
* @param[in] _context - A context that will be used by _action.
* @param[in] _runCount - How many times the function has to be executed.
* @param[in] _timePass - How much mili seconds have to pass until the next execute.
* @return A pointer to the task created.
* 
* @warning If _runCount equls 0 the function will run every _timePass.
*/
Task* TaskCreate (TaskActionFunction _action, void* _context, size_t _intervalTime);

/**
 * Frees the dynamic allocation of _task.
 * @param[in] _task - Task to destroy.
 */
 void TaskDestroy(Task* _task);


/**
* @brief run the task function.
* @param[in] _task - A pinter to the task.
* @return return 0 if task  is finish. 
*/
size_t TaskRun(Task* _task);


/**
* @brief get the next run of the task.
* @param[in] _task - A pinter to the task.
* @return return the next time of the task. 
*/

size_t GetNextRun(Task *_task);

/**
* @brief update the next time the task shulde be executed.
* @param[in] _task - A pointer to the task.
*  
*/

void TaskUpdate(Task *_task);

/**
* @brief get the time interval of the task.
* @param[in] _task - A pointer to the task.
* @return return the task interval.
*/

size_t GetTaskInterval(Task *_task);

/**
* @brief compare between two tasks.
* @param[in] _first - A pointer to the first task.
* @param[in] _first - A pointer to the second task.
* @return return 0 if the first is less.
*/


int TaskCompare(void *_first, void *_second);

 #endif /*__TASK_H__*/

 

