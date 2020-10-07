#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#define MAGIC_NUMBER 487232456

/* strcut of vector*/

struct Vector 
{
	int * m_items; /* pointer to the first index of the array */
	size_t m_originalSize; /* the original allocated size of the vector*/
	size_t m_size; /* the actual allocated size of the vector in any given moment*/
	size_t m_nitems; /* the number of items inside the vector*/
	size_t m_blockSize; /* chunk size of the vector. any realloc get 2 of this*/
	size_t m_magicNumber; /* magic number to prevented re_free*/
};

/* checks for create function */

ADTErr IsZero(size_t _initialSize, size_t _extensionBlockSize)
{
	if (_initialSize == 0 && _extensionBlockSize == 0)
	{
		return ERR_INVALID_INPUT;
	}
	return ERR_OK;
}

/* checks for the add function */

ADTErr CheckADD (Vector *_vector)
{
	if (_vector == NULL)
	{
		return ERR_NULL;
	}
	if (_vector -> m_size  == _vector -> m_nitems)
	{
		if (_vector -> m_blockSize == 0)
		{
			return ERR_OVERFLOW;
		}
	}
	return ERR_OK;
}

/* check if need realloc for the add function */

ADTErr NeedRealloc(Vector *_vector)
{
	int *temp_realloc;
	if ( _vector -> m_blockSize == 0)
	{
		return ERR_OVERFLOW;
	}
	temp_realloc = realloc(_vector -> m_items,(_vector -> m_blockSize + _vector -> m_size) *(sizeof(int)));
	if (temp_realloc == NULL)
	{
		return ERR_NOT_INITIALZED;
	}
	else
	{
		_vector -> m_items = temp_realloc;
		_vector -> m_size = _vector -> m_size + _vector -> m_blockSize;
	}
	return ERR_OK;
}

/* check int * for NULL and return enum */

ADTErr IntIsNull(int *_item)
{
	if (_item == NULL)
	{
		return ERR_NULL;
	}
	return ERR_OK;
}

/* check Vector for NULL and return enum */

ADTErr VectorIsNull(Vector *vector)
{
	if (vector == NULL)
	{
		return ERR_NULL;
	}
	return ERR_OK;
}

/* checks error for the delete function */

ADTErr ChecksForDelete(Vector *_vector, int *_item)
{
	if (VectorIsNull(_vector) == ERR_NULL || IntIsNull(_item) == ERR_NULL)
	{	
		return ERR_NULL;
	}
	if (_vector -> m_nitems  == 0)
	{
		return ERR_UNDERFLOW;
	}
	return ERR_OK;
}

/* checks and realloc for the delete function */

ADTErr CheckRealloc(Vector *_vector)
{
	int *TempRealloc;
	if ( (_vector -> m_size) - (_vector -> m_nitems) == (_vector -> m_blockSize) * 2)
	{
			if ((_vector -> m_size) - (_vector -> m_blockSize) >=  _vector -> m_originalSize)
			{
				TempRealloc = realloc(_vector -> m_items,(_vector -> m_size - _vector -> m_blockSize) *(sizeof(int)));
				if (TempRealloc == NULL)
				{
					return ERR_NULL;
				}
				if (TempRealloc != NULL)
				{
					_vector -> m_items = TempRealloc;
					_vector -> m_size =  _vector -> m_size - _vector -> m_blockSize;
				}
			}
	}
	return ERR_OK;
}

/* checks for the get func */

ADTErr CheckForGet(Vector *_vector, int *_item, int _index)
{
	if (VectorIsNull(_vector) == ERR_NULL || IntIsNull(_item) == ERR_NULL)
	{	
		return ERR_NULL;
	}
	if (_index <  0 || _index > _vector -> m_nitems)
	{
		return ERR_INVALID_INPUT;
	}
	return ERR_OK;
}

/* checks for the set func */

ADTErr ChecksForSet(Vector *_vector, int _item, int _index)
{
	if (VectorIsNull(_vector) == ERR_NULL)
	{	
		return ERR_NULL;
	}
	if (_index <  0 || _index > _vector -> m_nitems)
	{
		return ERR_INVALID_INPUT;
	}
	return ERR_OK;
}

/* checks for ItemsNum function */

ADTErr CheckForItemsNum(Vector *_vector, int *_numOfItems)
{
	if (_vector == NULL || _numOfItems == NULL)
	{	
		return ERR_NULL;
	}
	return ERR_OK;
}


















/* create the vector */

Vector * VectorCreate(size_t _initialSize, size_t _extensionBlockSize)
{
/* allocate two memory one for the vector and one for vector -> m_items */

	Vector *vectorAdress;
	if (IsZero( _initialSize, _extensionBlockSize) == ERR_INVALID_INPUT)
	{
		return NULL;
	}
	vectorAdress = (Vector *) malloc (sizeof(Vector));
	if (vectorAdress == NULL)
	{
		return NULL;
	}
	vectorAdress -> m_items = (int *) malloc (sizeof(int)*(_initialSize));
	if (vectorAdress -> m_items == NULL)
	{
		free(vectorAdress);
		return NULL;
	}

/* initialize the values in the vector */
 
	vectorAdress -> m_originalSize = _initialSize;
	vectorAdress -> m_size = _initialSize;
	vectorAdress -> m_nitems = 0;
	vectorAdress -> m_blockSize = 	_extensionBlockSize;
	vectorAdress -> m_magicNumber = MAGIC_NUMBER;
	return vectorAdress;
}




/* Destroy function */

void VectorDestroy(Vector * _vector)
{
	if ( _vector != NULL)
	{	
		if (_vector -> m_magicNumber == MAGIC_NUMBER)
		{
			free (_vector -> m_items);
			_vector -> m_magicNumber = 0;
			free (_vector);			
		}
	}
}





/* add one item function */

ADTErr VectorAdd (Vector *_vector, int _item)
{
	/* check if ERRORS */

	if (CheckADD (_vector) == ERR_NULL)
	{
		return ERR_NULL;
	}
	if (_vector -> m_size  == _vector -> m_nitems)
	{
		if (NeedRealloc(_vector) != ERR_OK)
		{
			return NeedRealloc(_vector);
		}
	}
	/* update Vector */
	_vector -> m_items[ _vector -> m_nitems] = _item;
	_vector -> m_nitems++;
	return ERR_OK;
}





/* delete one item function */	

ADTErr VectorDelete(Vector *_vector, int *_item)
{
	if (ChecksForDelete(_vector, _item) != ERR_OK)
	{
		return ChecksForDelete(_vector, _item);
	}
	if (CheckRealloc(_vector) == ERR_OK)
	{
		*_item = _vector -> m_items [_vector -> m_nitems-1];
		_vector -> m_nitems--;
	}
	return ERR_OK;
}





/* get function */

ADTErr VectorGet(Vector *_vector, size_t _index, int *_item)
{
	if (CheckForGet(_vector, _item, _index) != ERR_OK)
	{
		return CheckForGet(_vector, _item, _index);
	}
	*_item = _vector -> m_items [_index];
	return ERR_OK;	
}




/* set function */

ADTErr VectorSet(Vector *_vector, size_t _index, int _item)
{
	if (ChecksForSet(_vector, _item, _index) != ERR_OK)
	{
		return ChecksForSet(_vector, _item, _index);
	}
	(_vector -> m_items) [_index] = _item;
	return ERR_OK;
}



/* return items function */

ADTErr VectorItemsNum(Vector *_vector, int *_numOfItems)
{
	if (CheckForItemsNum(_vector, _numOfItems) != ERR_OK)
	{
		return CheckForItemsNum(_vector, _numOfItems);
	}
	else
	{
		*_numOfItems = _vector -> m_nitems;
	}
	return ERR_OK;
}



/* print function */

void VectorPrint(Vector * _vector)
{
	int index = 0;
	if (VectorIsNull (_vector) == ERR_OK)
	{
		for (; index < (_vector -> m_nitems); index++)
		{
			printf("%d",(_vector -> m_items)[index]);
			printf(" , ");	
		}
	}
}



































