#ifndef __VECTOR_H__
#define __VECTOR_H__


#include "ADTErr.h"
#include <stddef.h> /*size_t */

typedef struct Vector Vector;


/* this function create a vector by the size of initialSize.

input: 
	the function get to parameters
	1. _initialSize = which determine the size of the memory allocate to the vector's array,
	2. _extensionBlockSize = which determine the size of the memory that increse or decrese when needed.
output:
	this function return a pointer to the vector created by the function
	and allocated memory to the vector and to an array.
error:
	1. invalid input - initial size and extention block size can not be both 0. 
	2. NULL ERROR - if memory allocated for the vector and for the array get NULL.
*/

Vector * VectorCreate(size_t _initialSize, size_t _extensionBlockSize);


/* this function destroy the vector.

input:
	this function get a pointer to the vector need to be destroy.
output:
	free the memory allocated to the vector.
error:
	NULL ERROR - if the pionter is NULL.
*/

void VectorDestroy(Vector * _vector);



/* this function get a vector and an item and add the item to the 

last place of the array stored in vector. if block size is 0 and there is no free space

adding new items get an overflow error.

input:
	a pointer to vector and item to add to the array.
output:
	the item added to the last place of the array.

	return status.
errors:
	1. null error - if the vector is null function return ERR_NULL;

	2. OVERFLOW - if the number of items is equal to the number of size allocated, 

		       and block size is 0, function return ERR_OVERFLOW;		

*/
ADTErr VectorAdd (Vector *_vector, int _item);


/* this function get a vector and a pointer, delete the last item in the array 

and return the value of this item to the adress stored in the pointer. 

input:
	a pointer to vector and pointer to place to store deleted value.
output:
	the last item of the array is deleted and stored in the pointer's adress.

	return status.
errors:
	1. null error - if the vector is null function return ERR_NULL;
	
	2. underflow error - if the array is empty the function return ERR_UNDERFLOW;
	
*/
ADTErr VectorDelete(Vector *_vector, int *_item);


/* this function get a vector, a pointer and an index number and get

the value of the item in the index number of the array. the value will be stored 

in the adress stored in the pointer.

input:
	a pointer to vector, a pointer to a place to store the value

	and an index number.
output:
	return the value of the index number of the array.

	return status.
errors:
	1. null error - if the vector is null of pointer is null function return ERR_NULL;
	
	2. invalid input - if the index number is less than 0 or greater the the number of 
	
	items stored in the array the function return ERR_INVALID_INPUT;

*/
ADTErr VectorGet(Vector *_vector, size_t _index, int *_item);

/* this function get a vector, index number and a item and set

the value of the item on the index number of the array.

input:
	a vector, index number and an item to set.
output:
	change the value in the index place of the array to the item number.

	return status.
errors:
	1. null error - if the vector is null return ERR_NULL;
	
	2. invalid input - if the index number is less than 0 or greater the the number of 
	
	items stored in the array the function return ERR_INVALID_INPUT;
*/
ADTErr VectorSet(Vector *_vector, size_t _index, int _item);


/* this function get a vector and a pointer and return the number

of itemes stored in the array of the vector.

input:
	pointer to the vector and pointer to a place to store the number of items.
output:
	store the number of stored items in the pointer's adress.

	return status.
error:
	1. null error - if the vector is null or pointer os null return ERR_NULL;

*/
ADTErr VectorItemsNum(Vector *_vector, int *_numOfItems);
 
/* Unit Test functions */

/* this function print all the items in the array.

input:
	pointer to the vector.
output:
	print all the items in the array.
error:
	null error - if the vector is null;
	
*/
void VectorPrint(Vector * _vector); /* print array */

#endif /*__VECTOR_H__ */
