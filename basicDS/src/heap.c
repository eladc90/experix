#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "vector.h"
#define PARENT(x)((x - 1)/ 2)
#define LEFT(x)((x * 2) + 1)
#define RIGHT(x)((x * 2) + 2)
#define MAX(x, y)(x > y) ? x : y
#define SWAP(x, y)\
            {\
                int temp;\
                temp = (x);\
                (x) = (y);\
                (y) = temp;\
            } 
#define MAGIC_NUMBER 187187187
#define NULL_ERR -1
struct  Heap
{
    Vector *m_vector;
    size_t m_heapSize;
    int m_magicNumber;
};



static void Heapify(Heap *_heap, int _index);


/* --------------------------------------------   static functions -----------------------------------------------------*/


static void Heapify(Heap *_heap, int _index)
{
    int ptrParent = 0;
    int ptrLeft = 0;
    int ptrRight = 0;
    int max = 0;
    while (LEFT(_index) < _heap->m_heapSize)
    {
        VectorGet(_heap -> m_vector, _index, &ptrParent);
        VectorGet(_heap -> m_vector, LEFT(_index), &ptrLeft);
        if ( RIGHT(_index) < _heap->m_heapSize)
        {
            VectorGet(_heap -> m_vector,  RIGHT(_index), &ptrRight);
            max = MAX(ptrLeft, ptrRight);
        }
        else
        {
            max = ptrLeft;
        }
        if (max == ptrLeft && ptrParent < max)
        {   
            VectorSet(_heap -> m_vector, _index, max);
            VectorSet(_heap -> m_vector, LEFT(_index), ptrParent);
        }
        else if (max == ptrRight && ptrParent < max)
        {
            VectorSet(_heap -> m_vector, _index, max);
            VectorSet(_heap -> m_vector, RIGHT(_index), ptrParent);
        }
        _index++;
    }
}


static ADTErr bubbleUp(Heap *_heap)
{
    int ptrParent;   
    int ptrNew;
    int max;
    int index = _heap -> m_heapSize - 1;
    int parentIndex = PARENT(_heap -> m_heapSize);
    HeapPrint(_heap);
    printf("\n");
    VectorGet(_heap -> m_vector, parentIndex - 1, &ptrParent);
    VectorGet(_heap -> m_vector, index , &ptrNew);
    while (parentIndex  >= 0)
    {
        if (parentIndex == 0)
        {
            VectorGet(_heap -> m_vector, parentIndex , &ptrParent);
            max = MAX(ptrParent, ptrNew);
            if (max != ptrNew)
            {
                return ERR_OK;
            }
            VectorSet(_heap -> m_vector, parentIndex , max);
            VectorSet(_heap -> m_vector, index , ptrParent);
            break;
        }
        VectorGet(_heap -> m_vector, parentIndex - 1, &ptrParent);
        max = MAX(ptrParent, ptrNew);
        if (max != ptrNew)
        {
            return ERR_OK;
        }
        VectorSet(_heap -> m_vector, parentIndex -1, max);
        VectorSet(_heap -> m_vector, index , ptrParent);
        index = parentIndex - 1;
        parentIndex = PARENT(parentIndex);
    }
    return ERR_OK;
}



Heap *HeapBuild(Vector *_vector)
{
    int numOfElement = 0;
    Heap *newHeap;
    int index = 0;
    if (_vector == NULL)
    {
        return NULL;
    }
    newHeap = (Heap *) malloc (sizeof(Heap));
    if (newHeap == NULL)
    {
        return NULL;
    }
    newHeap -> m_vector = _vector; 
    VectorItemsNum(_vector, &numOfElement); 
    newHeap -> m_heapSize = numOfElement; 
    newHeap -> m_magicNumber = MAGIC_NUMBER;
    index = PARENT(newHeap -> m_heapSize - 1);
    for (; index >= 0; index--)
    {
        Heapify(newHeap, index);
    }
    return newHeap;
}



void HeapDestroy(Heap *_heap)
{
    if (_heap == NULL)
    {
        return;
    }
    if (_heap -> m_magicNumber == MAGIC_NUMBER)
    {
        _heap -> m_magicNumber = 0;
        free(_heap);
    }
}

ADTErr HeapInsert(Heap *_heap, int _data)
{
    if (_heap == NULL)
    {
        return ERR_NULL;
    }
    VectorAdd (_heap -> m_vector, _data);
    _heap -> m_heapSize++;
    bubbleUp(_heap);
    return ERR_OK;
}

ADTErr HeapMax(Heap *_heap, int* _data)
{
    if(_heap == NULL)
    {
        return ERR_NOT_INITIALZED;
    }
    return(VectorGet(_heap->m_vector,0,_data));
}

ADTErr HeapExtractMax(Heap *_heap, int* _data)
{
    int num;
    
    ADTErr err;
    if(_heap == NULL)
    {
        return ERR_NOT_INITIALZED;
    }
    err = HeapMax(_heap,_data);
    if(err == ERR_OK)
    {
        VectorGet(_heap->m_vector,_heap->m_heapSize-1,&num);
        VectorSet(_heap->m_vector,0,num);
    }
    return ERR_OK;
}

int HeapItemsNum(Heap *_heap)
{
    if(_heap == NULL)
    {
        return NULL_ERR;
    }
    return _heap->m_heapSize;
}

void HeapPrint(Heap *_heap)
{
    if(_heap == NULL)
    {
        return;
    }
    VectorPrint(_heap -> m_vector);
}


