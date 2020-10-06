#ifndef __TIME_H__
#define __TIME_H__
#include <stdlib.h>


typedef int (*CompareTimes)(size_t _a, size_t _b);
/** 
 * 
 * 
 * 
 *  @file  time.h
 *  @brief manage time.
 * get add and substract time.
 */



/**
 * @brief sleep.
 * @param[in] _waitTime - amount of time sleeping
 * 
 * 
 * 
 */
void TimerWait (long int _waitTime);

/**
* @brief compare between two elements.
* @param[in] _first - A pointer to the first element.
* @param[in] _first - A pointer to the second element.
* @return return 0 if the first is less.
*/


int TimeCompareLess(const void* _first, const void* _second);

/**
 * @brief calculate the time now.
 * @param[in] _timeGap - time pass from the stating time.
 * @return return the time now.
 * 
 */

long int TimeCalc (long int _timeGap);

/**
 * @brief calculate how much time to sleep.
 * @param[in] _dueTime.
 * @return return the time for sleeping.
 * 
 */

long int TimeSleep (long int _dueTime);


/**
 * @brief initiate the clock.
 * 
 * 
 * 
 */

void initGlClock();


 #endif /*__TIME_H__*/
