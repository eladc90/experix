#include <stddef.h> /*size_t*/
#include <stdlib.h> /* malloc */
#include "Task.h"
#include "timer.h"
#include "zlog.h" 





struct Task
{
	TaskActionFunction m_func;
	void * m_context;
	size_t m_intervalTime;
	size_t m_nextRunTime;
};



Task* TaskCreate (TaskActionFunction _action, void* _context, size_t _intervalTime)
{
	Task *newTask;
	if (_action == NULL || _intervalTime == 0)
	{
		return NULL;
	}
	newTask = (Task *) malloc (sizeof (Task));
	if (newTask == NULL)
	{
		return NULL;
	}
	
	newTask -> m_func = _action;
	newTask -> m_context = _context;
	newTask -> m_intervalTime = _intervalTime;
	newTask -> m_nextRunTime = _intervalTime;
	return newTask;
}


void TaskDestroy(Task* _task)
{
	free(_task);
}

size_t GetNextRun(Task *_task)
{
	return _task -> m_nextRunTime;
}

size_t GetTaskInterval(Task *_task)
{
	return _task -> m_intervalTime;
}


size_t TaskRun(Task* _task)
{
	size_t status;
	ZLOG(TRCAE, "task run");
	status = _task -> m_func(_task -> m_context);
	return status;
}

void TaskUpdate(Task *_task)
{
	_task -> m_nextRunTime += _task -> m_intervalTime;
	return;
}

int TaskCompare(void *_first, void *_second)
{
	Task* firstTask = (Task*)_first;
	Task* secondTask = (Task*)_second;
	return TimeCompareLess(&(firstTask ->  m_nextRunTime),&(secondTask ->  m_nextRunTime));
}























