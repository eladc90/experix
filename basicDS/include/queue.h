#ifndef __QUEUE_H__
#define __QUEUE_H__


#include "ADTErr.h"
#include <stdlib.h>

typedef struct Queue Queue;

/* 
this function create a queue by the size of _size

and return a pointer to the queue. cant get a size number of 0 or a very big size.

input:
	_size - determine the size of the queue.
output:
	return a pointer to the queue.
error:
	if size = 0 or size is too big return NULL.
	
	if can't initialized queue return NULL.
*/

Queue* QueueCreate (size_t _size);

/*
 this function destroy the queue.

input:
	get a pointer to a queue.
output:
	destroy the queue.
error:
*/

void QueueDestroy (Queue *_queue);

/*
this function get a queue and an item and insert the

item to the last available place in the queue.

input:
	a pointer to a queue and an item to insert.
output:
	insert the item to the last place in the queue. return ERR_OK.
errors:
	1. ERR_NULL - if the queue is NULL
	
	2. ERR_OVERFLOW - if the queue is full and cant get a new item.

*/

ADTErr QueueInsert (Queue *_queue, int _item);

/*
this function get a queue and an pointer, remove the first item in

the queue and return is value to the pointer.

input:
	a pointer to store the item and a queue.
output:
	get the value of the first in queue. return ERR_OK.
errors:
	1. ERR_NULL - if queue is NULL or the pointer _item is NULL.
	
	2. ERR_UNDERFLOW - if the queue is empty and can't remove any more items.
	


*/

ADTErr QueueRemove (Queue *_queue, int *_item);

/*
this function get a queue and return if this queue is empty or not.

input:
	a queue.
output:
	return 1 if the queue is empty and 0 if not.
error:
	NULL - return 0 if the queue is NULL.
*/

int QueueIsEmpty (Queue *_queue);

/*
this function print all items in queue from first to last.

*/
void QueuePrint(Queue *_queue);





#endif /*__QUEUE_H__ */
