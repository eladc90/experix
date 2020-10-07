#include <stdlib.h>
#include <stdio.h>
#include "myMalloc.h"
#define MAGIC_NUMBER 0XCAFEFEED
#define UN_MAGIC_NUMBER 0XCDCDCDCD

#define POOL_TEST(head) (head == NULL || head -> m_magicNumber != MAGIC_NUMBER) 
#define SIZE_OF_POINTER 8

struct Pool
{
	size_t m_magicNumber;
	Node *m_head;
	void *m_pool;
	Node *m_end;
	size_t m_sizeOfBuffer;
};

struct Node
{
	void *m_next;
	void *m_prev;
	size_t m_size;
};


Pool *MyMallocCreate(size_t _sizeOfBuffer)
{
	Pool *pool;
	if (_sizeOfBuffer == 0)
	{
		return NULL;
	}
	if (_sizeOfBuffer % SIZE_OF_POINTER != 0)
	{
		_sizeOfBuffer += SIZE_OF_POINTER - (_sizeOfBuffer % SIZE_OF_POINTER);
	}
	
	pool = (Pool *) malloc (_sizeOfBuffer + sizeof(Pool));
	if (pool == NULL)
	{
		return NULL;
	}
	
	pool -> m_head = (Node*)((char*) pool + sizeof(Pool));
	pool -> m_sizeOfBuffer = _sizeOfBuffer;
	pool -> m_magicNumber = MAGIC_NUMBER;
	
	(pool -> m_head)-> m_next = (char*)(pool -> m_head) + _sizeOfBuffer;
	pool -> m_end = (pool -> m_head + (_sizeOfBuffer + sizeof(Pool)));
	pool -> m_end -> m_next = NULL;
	return pool;
}



void MyMallocDestroy(Pool *_head)
{
	if (POOL_TEST(_head))
	{
		return;
	}
	
	_head -> m_magicNumber = UN_MAGIC_NUMBER;
	free(_head -> m_pool);
	free(_head);
	return;
}


void *MyMalloc(Pool *_pool, size_t _blockSize)
{
	void *returnAdd;
	
	if (POOL_TEST(_pool))
	{
		return NULL;
	}
	if (_pool -> m_head == NULL)
	{
		return NULL;
	}
	
	returnAdd = (_pool -> m_head, _blockSize);
	if (returnAdd == NULL)
	{
		return NULL;
	}
	_pool -> m_head = _pool -> m_head + _pool -> m_sizeOfBuffer;
	
	
	((Node*)(_pool -> m_head))-> m_next = _pool -> m_head + _blockSize;
	
	return returnAdd;
}


void Myfree(Pool *_pool , void *_buffer)
{
	if (POOL_TEST(_pool ) || _buffer == NULL)
	{
		return;
	}
	
	((Node*)_buffer) -> m_next = _pool -> m_head;
	_pool -> m_head = _buffer;
	return;
}

static void *ReturnIfExit(Node *_head, size_t _blockSize)
{
	Node *node = _head;
	while(node -> m_next != NULL)
	{
		if (node -> m_size >= _blockSize)
		{
			return node;
		}
		node = node -> m_next;
	}
}






