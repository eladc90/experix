#ifndef __HEAP_H__
#define __HEAP_H__

#include "vector.h"

typedef struct  Heap Heap;

/* this function build a heap

input:
    a pointer to vector
output:
    return a pointer to the heap
error:
    if vector is null or allocation failed - return null
*/

Heap *HeapBuild(Vector *_vector);

/* this function destory the heap

input:
    a pointer to the heap
output:
    none
error:
*/

void HeapDestroy(Heap *_heap);

/* this function insert data to the heap

input:
    a pointer to the heap and data to insert
output:
    return ERR_OK if insert the data
error:
    ERR_NOT_INITIALZED - if vector is null
*/

ADTErr HeapInsert(Heap *_heap, int _data);

/* this function return the max value in the heap

input:
    a pointer to the heap and pointer to put the data
output:
    return ERR_OK 
error:
    ERR_NOT_INITIALZED - if heap is null
*/

ADTErr HeapMax(Heap *_heap, int* _data);

/*  this function extract the max value in the heap

input:
    a pointer to the heap and a pointer to put the data
output:
    return ERR_OK
error:
    ERR_NOT_INITIALZED - if the heap is NULL
*/


ADTErr HeapExtractMax(Heap *_heap, int* _data);

/* this function return how much items in the heap

input:
    a pointer to the heap
output:
    return the number of items in the heap
error:
    NULL - if the heap is null
*/

int HeapItemsNum(Heap *_heap);

void HeapPrint(Heap *_heap);









#endif /*__HEAP_H__ */




