#ifndef __PQUEUE_H__
#define __PQUEUE_H__



typedef struct Pqueue Pqueue;


/** 
 * 
 * 
 * 
 *  @file  Pqueue.h
 *  @brief create and desrtoy priority queue.
 * 
 */

/**
 * @brief create a new pQeueue.
 * @return A pointer to the pQeueu created.
 * 
 * @warning If allocation fail return NULL.
 */

Pqueue* PqeueuCreate();




/**
 * @brief insert data to the   pQeueue.
 * @param[in] _pqeueu - a pointer to the PQueue.
 * @param[in] _element - a pointer tot the data.
 * @warning If pqueue NULL retrun NULL.
 */

int PqueueInsert(Pqueue *_pqueue, void *_element);

/**
 * @brief extract the first data in the    pQeueue.
 * @param[in] _pqeueu - a pointer to the PQueue.
 * 
 * @warning If pqueue NULL retrun NULL.
 */

void *PqueueExtract(Pqueue *_pqueue);

/**
 * @brief destroy the pQeueue.
 * @param[in] _pqeueu - a pointer to the PQueue.
 * @param[in] _elementDestroy - a pointer to function to destroy the data.
 * @warning If pqueue NULL retrun NULL or _elementDestroy.
 */

void PqueueDesroy(Pqueue *_pqueue, void (*_elementDestroy) (void*));

 #endif /*__PQUEUE_H__*/

