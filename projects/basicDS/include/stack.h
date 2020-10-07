#ifndef __STACK_H__
#define __STACK_H__

#include"vertor_err.h"
#include <stddef.h> /*size_t */

typedef struct Stack Stack;


/* this function create a stack by the size of initialSize.

input: 
	the function get to parameters
	1. _initialSize = which determine the size of the memory allocate to the stack's array,
	2. _extensionBlockSize = which determine the size of the memory that increse or decrese when needed.
output:
	this function return a pointer to the stack created by the function.
error:
	1. invalid input - initial size and extention block size can not be both 0. 
	
*/

Stack *StackCreate (size_t _size, size_t _blockSize);

/* this function destroy the stack.

input:
	this function get a pointer to the stack need to be destroy.
output:
	free the memory allocated to the stack.
error:
	NULL ERROR - if the pionter is NULL.
*/

void StackDestroy (Stack * _stack);

/* this function get a stack and an item and add the item to the 

last place of the array stored in stack. if block size is 0 and there is no free space

adding new items get an overflow error.

input:
	a pointer to stack and item to add to the array.
output:
	the item added to the last place of the array.

	return status.
errors:
	1. null error - if the stack is null function return ERR_NULL;

	2. OVERFLOW - if the number of items is equal to the number of size allocated, 

		       and block size is 0, function return ERR_OVERFLOW;		

*/

ADTErr StackPush (Stack * _stack, int _item);

/* this function get a stack and a pointer, delete the last item in the array 

and return the value of this item to the adress stored in the pointer. 

input:
	a pointer to stack and pointer to place to store deleted value.
output:
	the last item of the array is deleted and stored in the pointer's adress.

	return status.
errors:
	1. null error - if the stack is null function return ERR_NULL;
	
	2. underflow error - if the array is empty the function return ERR_UNDERFLOW;
	
*/

ADTErr StackPop (Stack * _stack, int * _item);

/* this function get a stack and a pointer and get the value of the last item of the array. the value will be stored 

in the adress stored in the pointer.

input:
	a pointer to stack and a pointer to a place to store the value.
output:
	get the value the last item of the array.

	return status.
errors:
	1. null error - if the stack is null or pointer is null function return ERR_NULL;
	
	return status.

*/

ADTErr StackTop (Stack * _stack, int * _item);

/* this function get a stack and return if this stack is empty.

input:
	a pointer to a stack.
output:
	return 0 if stack is empty and 1 if not.
error:
	return 0 if stack is NULL.
*/

int StacklIsEmpty (Stack * _stack);

/* unit-test functions */

/* this function print all the items in the array.

input:
	pointer to the stack.
output:
	print all the items in the array.
error:
	null error - if the stack is null;
	
*/
void StackPrint (Stack * _stack);


#endif /* __STACK_H__ */


