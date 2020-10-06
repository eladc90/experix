#include "timer.h"
#include "Task.h"
#include <time.h>   /*timespec , clock_gettime */
#include <unistd.h> /* usleep */
#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define SEC_TO_MILISEC(x)(x * 1000)
#define MILI_TO_MICRO(x)(x * 1000)
#define NAN_TO_MIL(x)(x / 1000)

static struct timespec g_timeSpe;


int TimeCompareLess(const void* _first, const void* _second)
{
	size_t first = GetNextRun((Task *)_first);
	size_t second = GetNextRun((Task *)_second);
	return (first  < second) ? TRUE : FALSE;
}

void initGlClock()
{
	int status;
	clockid_t clkId = CLOCK_MONOTONIC;
	status = clock_gettime(clkId, &g_timeSpe);
	if (status)
	{
		return;		
	}
	return;
}

long int TimeCalc (long int _timeGap)
{	
	return NAN_TO_MIL(g_timeSpe.tv_nsec) + _timeGap;	
}

long int TimeSleep (long int _dueTime)
{

	int status;
	struct timespec timeSpe;
	clockid_t clk_id = CLOCK_MONOTONIC;
	long int waitTime;
	long int dueTime = TimeCalc(_dueTime);
	status = clock_gettime(clk_id, &timeSpe);
	if (status)
	{
		return 0;		
	}

	waitTime = dueTime - NAN_TO_MIL(timeSpe.tv_nsec);
	return (waitTime > 0) ? waitTime : 0;
}

void TimerWait (long int _waitTime)
{
	_waitTime = (_waitTime < 0) ? 0 : _waitTime;
	usleep(_waitTime / 1000);
}



 
