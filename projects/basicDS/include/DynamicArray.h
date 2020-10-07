#include <stdio.h>

enum status{
	REALOC_ERROR,
	UNDERFLOW_ERROR,
	NULL_ERROR,
	OVERFLOW_ERROR,
	INVALID_INPUT_ERROR,
	OK
};


typedef struct DynamicArray DynamicArray;

/*sorry I was to tired to write down nice description, will do it tomorrow */

/*
ERRORS:
	NULL - size can't be a negative number, or allocation fail
INPUT:
	Number of integer that we want our array to be able to contain 
OUTPUT:
	pointer for a dynamic array in the size of sizeof(int)*size 
*/
DynamicArray* DynamicArrayCreate(int size, int blockSize);
/*
Description:
	disallocates the array (free(*DynamicArrayPtr)) 
ERROR:
	NULL - *DynamicArrayPtr can't be null 
INPUT:
	*DynamicArrayPtr - pointer for a dynamic integer array

*/
void DynamicArrayDestroy(DynamicArray* DynamicArrayPtr);

/*
ERRORS:
	NULL_ERROR - all pointers can't be null 
	REALOC_ERROR - Realoc couldn't function 
	OVERFLOW_ERROR - happens when IncBlockSize = 0, and the array needs to expand
	INVALID_INPUT_ERROR - ...

INPUT:
	**DynamicArrayPtr - pointer for a dynamic integer array (array might realocate)
	Data - Int to append to the  list
	DaSize - Size of the dynamic integer array
	DaNumOfElements - number of elements in the list of integers
	IncBlockSize - if array is to short to contain the list, realoc it by IncBlockSize
OUTPUT:
	status:
		OK (two options)-
			 1. Data was added to the end of the list in the dinamic array (or the begining if the array is empty) 
			 2. list was to short and Realocated, **DynamicArrayPtr was updated
*/


int DynamicdArrayInsert(DynamicArray* DynamicArrayPtr,int Data);


/*
ERRORS:
	INVALID_INPUT -...
	NULL_ERROR - all pointers can't be null
	UNDERFLOW_ERROR - happens when IncBlockSize = 0, and the array needs to expand

INPUT:
	*DynamicArrayPtr - pointer for a dynamic integer array
	*data - pointer to where the deleted integer will be saved
	*DaNumOfElements - pointer to number of elements in the list of integers

OUTPUT:
	status -
		OK - Data was removed from list
*/
int DynamicArrayDelete(DynamicArray* DynamicArrayPtr, int* Data);
