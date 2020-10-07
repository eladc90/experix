#include "queue.h"
#include <stdlib.h>
#define IS_EMPTY 1
#define IS_NOT_EMPTY 0
#define MAGIC_NUMBER 0xB16B00B5

/*============================== static function =============================*/

static Queue_Result CheckEnqueue(Queue* _queue);

static Queue_Result CheckDequeue(Queue* _queue, void** _pValue);

/*============================================================================*/



struct Queue
{
	size_t m_magicNumber;
	void **m_queue;    
	size_t m_size; 
	size_t m_head; 
	size_t m_tail; 
	size_t m_nitems; 
};




Queue* QueueCreate(size_t _maxSize)
{
    Queue *QueueAdress;
    void **queArr;
	if (_maxSize == 0)
	{
		return NULL;
	}	
	QueueAdress = (Queue *) malloc (sizeof(Queue));
	if (QueueAdress == NULL)
	{
		return NULL;
	}
	queArr = (void ** )malloc (sizeof(void *) * _maxSize);
	if (queArr == NULL)
	{
		free(QueueAdress);
		return NULL;
	}
	
	QueueAdress -> m_size = _maxSize;
	QueueAdress -> m_nitems = 0;
	QueueAdress -> m_head = 0;
	QueueAdress -> m_tail = 0;
   	QueueAdress -> m_queue = queArr;
	QueueAdress -> m_magicNumber = MAGIC_NUMBER;
	return QueueAdress;
}



void QueueDestroy(Queue** _queue, void (*_elementDestroy)(void* _item))
{
    size_t index = 0;
    if (_queue == NULL || *_queue == NULL || _elementDestroy == NULL ||(*_queue) -> m_magicNumber != MAGIC_NUMBER)
    {
        return;
    }
	(*_queue) -> m_magicNumber = 0;
    for (; index < (*_queue) -> m_nitems; index++)
	{
		_elementDestroy((*_queue) -> m_queue[index]);		
	}
	free ((*_queue) -> m_queue);
    free(*_queue);
    *_queue = NULL;
	return;
}


Queue_Result QueueEnqueue(Queue* _queue, void* _item)
{
    int status = CheckEnqueue(_queue);
    if (status != QUEUE_SUCCESS)
    {
        return status;
    }
    _queue -> m_queue[_queue -> m_tail] = _item;
    _queue -> m_tail  = (_queue -> m_tail + 1) % (_queue -> m_size);
    _queue -> m_nitems++;
    return QUEUE_SUCCESS;
}

Queue_Result QueueDequeue(Queue* _queue, void** _pValue)
{
    int status = CheckDequeue(_queue, _pValue);
    if (status != QUEUE_SUCCESS)
    {
        return status;
    }
    *_pValue = _queue -> m_queue[_queue -> m_head];
	_queue -> m_head = (_queue -> m_head + 1) % (_queue -> m_size);
	_queue -> m_nitems--;
    return QUEUE_SUCCESS;
}

int QueueIsEmpty(const Queue* _queue)
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

size_t QueueForEach(const Queue* _queue, QueueElementAction _action, void* _context)
{
	void *elem;
	size_t index = 0;
	
	if( (_queue == NULL) || (_queue->m_queue == NULL) || (_queue->m_nitems < 1))
	{
		return index;
	}
	
	for(; index < _queue-> m_nitems ; index++ )
	{
		elem = _queue->m_queue[index];
		if( _action( elem, index, _context ) == 0)
		{
			break;
		}
	}
	return index;
	
}

/*=========================================== aux functions =========================================*/

static Queue_Result CheckDequeue(Queue* _queue, void** _pValue)
{
    if (_queue == NULL || _pValue == NULL)
    {
        return QUEUE_NULL_ERR;
    }
    if (_queue -> m_nitems == 0)
    {
        return QUEUE_UNDERFLOW;
    }
    return QUEUE_SUCCESS;
}

static Queue_Result CheckEnqueue(Queue* _queue)
{
    if (_queue == NULL)
    {
        return QUEUE_NULL_ERR;
    }
    if (_queue -> m_nitems == _queue -> m_size)
    {
        return QUEUE_OVERFLOW;
    }
    return QUEUE_SUCCESS;
}

