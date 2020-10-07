#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "ADTErr.h"

#define IS_EMPTY 1
#define IS_NOT_EMPTY 0
#define MAGIC_NUMBER 487232456

struct Queue
{
	int* m_que;    /* pointer to the queue array */
	size_t m_size; /* size of memory of the array */
	size_t m_head; /* index of the first */
	size_t m_tail; /*index of the last item */
	size_t m_nitems; /* number of items in the array */
	int m_magicNumber; /* magic number for check double free */
};	

Queue *QueueCreate (size_t _size)
{
	Queue *QueueAdress;
	if (_size == 0)
	{
		return NULL;
	}	
	QueueAdress = (Queue *) malloc (sizeof(Queue));
	if (QueueAdress == NULL)
	{
		return NULL;
	}
	QueueAdress -> m_que = (int *)malloc (sizeof(int) * (_size));
	if (QueueAdress -> m_que == NULL)
	{
		free(QueueAdress);
		return NULL;
	}
	
	QueueAdress -> m_size = _size;
	QueueAdress -> m_nitems = 0;
	QueueAdress -> m_head = 0;
	QueueAdress -> m_tail = 0;
	QueueAdress -> m_magicNumber = MAGIC_NUMBER;
	return QueueAdress;
}


void QueueDestroy (Queue *_queue)
{
	if (_queue != NULL && _queue -> m_magicNumber == MAGIC_NUMBER)
	{
		free (_queue -> m_que);
		_queue -> m_magicNumber = 0;
		free(_queue);
	}
}

ADTErr QueueInsert (Queue *_queue, int _item)
{
	if (_queue == NULL)
	{
		return ERR_NULL;
	}
	if (_queue -> m_head == _queue -> m_tail && _queue -> m_nitems > 0)
	{
		return ERR_OVERFLOW;
	}
	_queue -> m_que[_queue -> m_tail] = _item;
	_queue -> m_tail  = (_queue -> m_tail + 1) % (_queue -> m_size);
	_queue -> m_nitems++;
	return ERR_OK;
}


ADTErr CheckForRemove (Queue *_queue, int *_item)
{
	if (_queue == NULL || _item == NULL)
	{
		return ERR_NULL;
	}
	if (_queue -> m_head == _queue -> m_tail && _queue -> m_nitems == 0)
	{
		return ERR_UNDERFLOW;
	}
	return ERR_OK;
}

ADTErr QueueRemove (Queue *_queue, int *_item)
{
	if (CheckForRemove (_queue, _item) != ERR_OK)
	{
		return CheckForRemove (_queue, _item);
	}
	*_item = _queue -> m_que[_queue -> m_head];
	_queue -> m_head = (_queue -> m_head + 1) % (_queue -> m_size);
	_queue -> m_nitems--;
	return ERR_OK;
}


int QueueIsEmpty (Queue *_queue)
{
	if (_queue == NULL)
	{
		return 0;
	}
	if (_queue -> m_head == _queue -> m_tail && _queue -> m_nitems == 0)
	{
		return IS_EMPTY;
	}
	return IS_NOT_EMPTY;
}

void QueuePrint(Queue *_queue)
{
	int headIndex;
	int index;
	if (_queue != NULL)
	{
		for (index = 0, headIndex = _queue -> m_head; index < _queue -> m_nitems; index++, headIndex = (headIndex + 1) % (_queue -> m_size))
		{
			printf("this is th queue: %d ",(_queue -> m_que)[headIndex]);
		}	
	}	
}



int getSize(Queue *_queue)
{
	int size;
	size = _queue -> m_size;	
	return size;
}





















