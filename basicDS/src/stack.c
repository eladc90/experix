#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "vector.h"

#define MAGIC_NUMBER 487232456

struct Stack
{
	Vector *m_vector;
	int m_magicNumber;
};

Stack *StackCreate (size_t _size, size_t _blockSize)
{
	Stack *StackAdress;
	StackAdress = (Stack *) malloc (sizeof(Stack));
	if (StackAdress == NULL)
	{
		return NULL;
	}
	StackAdress -> m_vector = VectorCreate(_size, _blockSize);
	if (StackAdress -> m_vector == NULL)
	{
		return NULL;
	}
	StackAdress -> m_magicNumber = MAGIC_NUMBER;
	return StackAdress;
}

void StackDestroy (Stack * _stack)
{	
	if (_stack != NULL)
	{
		if (_stack -> m_magicNumber == MAGIC_NUMBER)
		{
			_stack -> m_magicNumber = 0;
			VectorDestroy(_stack -> m_vector);
			free(_stack);
		}
	}	
}

ADTErr StackPush (Stack * _stack, int _item)
{
	if (_stack == NULL)
	{
		return ERR_NULL;
	}
	VectorAdd (_stack -> m_vector, _item);
	return ERR_OK;

}


ADTErr StackPop (Stack * _stack, int * _item)
{
	if (_stack == NULL)
	{
		return ERR_NULL;
	}
	VectorDelete (_stack -> m_vector, _item);
	return ERR_OK;
}

ADTErr StackTop (Stack * _stack, int * _item)
{
	size_t ptr;
	int tempNum;
	size_t index;
	if (_stack == NULL)
	{
		return ERR_NULL;
	}
	index = VectorItemsNum (_stack -> m_vector, &ptr);
	VectorGet (_stack -> m_vector, index -1, _item);
	return ERR_OK;
}


int StacklIsEmpty (Stack * _stack)
{
	size_t ptr;
	int tempNum;
	size_t index;
	if (_stack == NULL)
	{
		return 0;
	}
	index = VectorItemsNum (_stack -> m_vector, &ptr);
	if (ptr == 0)
	{
		return 0;
	}
	if (ptr > 0)	
	{
		return 1;
	}
}

void StackPrint (Stack * _stack)
{
	if (_stack != NULL)
	{
		VectorPrint (_stack -> m_vector);
	}
	
}




