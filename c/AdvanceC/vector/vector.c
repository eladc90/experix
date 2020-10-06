#define NDEBUG
#include <assert.h>
#include <stdlib.h>
#include "vector.h"
#include <stdio.h>
#define MAGIC_NUMBER 4824896231


struct Vector
{
	size_t m_magicNumber;
	void **m_array;
	size_t m_capacity;
	size_t m_blockSize;
	size_t m_numOfElement;
	size_t m_initialSize;
};


/* =========================== static function ==================================*/

static Vector_Result CheckAppend (Vector* _vector);

static Vector_Result VectorRealloc(Vector *_vector);

static Vector_Result CheckRemove (Vector* _vector, void** _pValue);

static Vector_Result CheckGet(const Vector* _vector, size_t _index);

static Vector_Result CheckSet(Vector* _vector, size_t _index);

/*================================================================================*/



Vector* VectorCreate(size_t _initialCapacity, size_t _blockSize)
{
	Vector *vec = NULL;
	void **array = NULL;
	if (_initialCapacity == 0 && _blockSize == 0)
	{
		return NULL;
	}
	vec = (Vector *) malloc (sizeof(Vector));
	if (vec == NULL)
	{
		return NULL;
	}

	if (_initialCapacity == 0)
	{
		vec -> m_array = NULL;
	}

	else 
	{
		array = (void **) malloc (sizeof(void *) * _initialCapacity + 1);
	}
	if (array == NULL)
	{
		free (vec);
		return NULL;
	}


	vec -> m_capacity = _initialCapacity;
	vec -> m_blockSize = _blockSize;
	vec -> m_numOfElement = 0;
	vec -> m_initialSize = _initialCapacity;
	vec -> m_array = array;
	vec -> m_magicNumber = MAGIC_NUMBER;
	return vec;
}


void VectorDestroy(Vector** _vector, void (*_elementDestroy)(void* _item))
{
	size_t index = 0;
	if (_vector == NULL || *_vector == NULL )
	{
		return;
	}
	if ((*_vector) -> m_magicNumber != MAGIC_NUMBER)
	{
		return;
	}
	else 
	{
		(*_vector) -> m_magicNumber = 0;
	}
	if (_elementDestroy != NULL)
	{
		for (; index < (*_vector) -> m_numOfElement; index++)
		{
			_elementDestroy( (*_vector) -> m_array[index]);		
		}
	}
	free( (*_vector) -> m_array);
	free(*_vector);
	*_vector = NULL;
}

Vector_Result VectorAppend(Vector* _vector, void* _item)
{	
	int status = CheckAppend(_vector);
	if (status == VECTOR_NEED_REALLOC)
	{
		VectorRealloc (_vector);	
	}
	if (status != VECTOR_SUCCESS && status != VECTOR_NEED_REALLOC)
	{
		return status;
	}
	_vector -> m_numOfElement++;
	_vector -> m_array[_vector -> m_numOfElement] = _item;
	return VECTOR_SUCCESS;
}


Vector_Result VectorRemove(Vector* _vector, void** _pValue)
{
	int status;
	status = CheckRemove ( _vector,  _pValue);
	if (status != VECTOR_SUCCESS)
	{
		return status;
	}
	*_pValue = _vector -> m_array [ _vector -> m_numOfElement];
	_vector -> m_numOfElement--;
	return VECTOR_SUCCESS;
}


Vector_Result VectorGet(const Vector* _vector, size_t _index, void** _pValue)
{
	int status;
	status = CheckGet(_vector, _index);
	if (status != VECTOR_SUCCESS)
	{
		return status;
	}
	*_pValue = _vector -> m_array[_index];
	return VECTOR_SUCCESS;
}




Vector_Result VectorSet(Vector* _vector, size_t _index, void*  _value)
{
	int status;
	status = CheckSet(_vector, _index);
	if (status != VECTOR_SUCCESS)
	{
		return status;
	}
	_vector -> m_array [_index] = _value;
	return VECTOR_SUCCESS;
}




size_t VectorSize(const Vector* _vector)
{
	if (_vector != NULL)
	{
		return _vector -> m_numOfElement;
	}
	return 0;
}


size_t VectorCapacity(const Vector* _vector)
{
	if (_vector != NULL)
	{
		return _vector -> m_capacity;
	}
	return 0;
}


size_t VectorForEach(const Vector* _vector, VectorElementAction _action, void* _context)
{
	void* element;
	size_t index = 0;
	if (_action == NULL)
	{
		return index;
	}
	while (VectorGet(_vector, ++index , &element) == VECTOR_SUCCESS)
	{	
		if (_action (element, index, _context) == 0)
		{
			break;
		}
	}
	return index - 1;
}


/*=========================================== aux functions =========================================*/


static Vector_Result CheckAppend (Vector* _vector)
{
	if (_vector == NULL)
	{
		return VECTOR_NULL;
	}
	if (_vector -> m_capacity == _vector -> m_numOfElement && _vector -> m_blockSize == 0)
	{
		return VECTOR_OVERFLOW;
	}
	if (_vector -> m_capacity == _vector -> m_numOfElement && _vector -> m_blockSize > 0)
	{
		return VECTOR_NEED_REALLOC;
	}
	return VECTOR_SUCCESS;
}



static Vector_Result VectorRealloc(Vector *_vector)
{
	void **temp;
	temp = realloc ( _vector -> m_array, sizeof(void *) * (_vector -> m_numOfElement + _vector -> m_blockSize));
	if (_vector == NULL)
	{
		return VECTOR_NULL;
	}
	_vector -> m_array = temp;
	_vector -> m_capacity += _vector -> m_blockSize;
	return VECTOR_SUCCESS;
}


static Vector_Result CheckRemove (Vector* _vector, void** _pValue)
{
	if (_vector == NULL || _pValue == NULL)
	{
		return VECTOR_NULL;
	}
	if ( _vector -> m_numOfElement == 0)
	{
		return VECTOR_UNDERFLOW;	
	}
	return VECTOR_SUCCESS;
}	

static Vector_Result CheckGet(const Vector* _vector, size_t _index)
{
	if (_vector == NULL)
	{
		return VECTOR_NULL;
	}
	if (_index > _vector -> m_numOfElement || _index == 0)
	{
		return VECTOR_INDEX_OUT_OF_BOUNDS_ERROR;
	}
	return VECTOR_SUCCESS;
}

static Vector_Result CheckSet(Vector* _vector, size_t _index)
{
	if (_vector == NULL)
	{
		return VECTOR_NULL;
	}
	if (_index > _vector -> m_numOfElement || _index == 0)
	{
		return VECTOR_INDEX_OUT_OF_BOUNDS_ERROR;
	}
	return VECTOR_SUCCESS;
}




















