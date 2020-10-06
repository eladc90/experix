#include "heap.h"
#include "vector.h"
#include <stdlib.h> /* malloc */
#define MAGIC_NUMBER 0XBEEFBEEF
#define UN_MAGIC_NUMBER 0XDEEFBEEF
#define PARENT(x)((x)/ 2)
#define LEFT(x)(x * 2)
#define RIGHT(x)((x * 2) + 1)
#define MAX(x, y)(x > y) ? x : y

struct  Heap
{
    Vector *m_vector;
    size_t m_heapSize;
    int m_magicNumber;
    LessThanComparator m_func;
};

/* ======================================== statics functions  ======================================== */

static void swap(Vector* _vec, size_t _indexA, size_t _indexB);

static void heapify(Vector *_vector,  LessThanComparator _pfLess);

static void bubbleUp(Heap *_heap);

static void SortHeapify(Vector *_vector,  LessThanComparator _pfLess, int _index);

static int CheckDupli(void *_element,size_t  ind,void *_context);

/* ==================================================================================================== */


Heap* HeapBuild(Vector* _vector, LessThanComparator _pfLess)
{
    Heap *newHeap;
    newHeap = (Heap *) malloc (sizeof(Heap));
    if (_vector == NULL || newHeap == NULL || _pfLess == NULL)
    {
        return NULL;
    }
    newHeap -> m_vector = _vector; 
    newHeap -> m_heapSize = VectorSize(_vector); 
    newHeap -> m_magicNumber = MAGIC_NUMBER;
    newHeap -> m_func = _pfLess;
    heapify(_vector,  _pfLess);
    return newHeap;
}




static void heapify(Vector *_vector,  LessThanComparator _pfLess)
{
    size_t index = VectorSize(_vector);
    void *left;
    void *right;
    void *father;
    
    if (index == 0)
    {
        return;
    }
    
    index = PARENT(index);
    while (index > 0)
    {
        VectorGet(_vector, LEFT(index), &left);
        VectorGet(_vector, index, &father);
        if (RIGHT(index) <= index)
        {
            VectorGet(_vector, index, &right);
            if (_pfLess(left, father))
            {
                swap(_vector, LEFT(index), index);
            }
            else
            {
                swap(_vector, RIGHT(index), index);
            }
        }
        else
        {
            if (_pfLess(left, father))
            {
                swap(_vector, LEFT(index), index);
            }
        }
        index--;
    }
}


static void swap(Vector* _vec, size_t _indexA, size_t _indexB)
{
	void *a, *b;
	VectorGet(_vec, _indexA, &a);
	VectorGet(_vec, _indexB, &b);
	VectorSet(_vec, _indexA, b);
	VectorSet(_vec, _indexB, a);
}



Vector* HeapDestroy(Heap** _heap)
{
    Vector *temp;
    if (_heap == NULL || *_heap == NULL)
    {
        return NULL;
    }
    temp = (*_heap) -> m_vector;
    if ((*_heap) -> m_magicNumber == MAGIC_NUMBER)
    {
        (*_heap) -> m_magicNumber = UN_MAGIC_NUMBER;
        free(*_heap);
        *_heap = NULL;
    }
    return  temp;
    
} 


HeapResult HeapInsert(Heap* _heap, void* _element)
{
    int dup;
    Vector_Result status;
    if (_heap == NULL || _element == NULL)
    {
        return HEAP_NOT_INITIALIZED;
    }
    status = VectorAppend (_heap -> m_vector, _element);
    if (status == VECTOR_OVERFLOW)
    {
        return HEAP_OVERFLOW;
    }
    dup = HeapForEach (_heap ,(ActionFunction) CheckDupli, _element);
    if (dup != _heap -> m_heapSize)
    {
        return HEAP_DUPLICATION;
    }
    _heap -> m_heapSize++;
    bubbleUp(_heap);
    heapify(_heap -> m_vector, _heap -> m_func);
    return HEAP_SUCCESS;
}

static void bubbleUp(Heap *_heap)
{
    void *son;
    void *father;
    size_t sonIndex = _heap -> m_heapSize;
    size_t fatherIndex =  PARENT(sonIndex);

    while (fatherIndex > 0)
    {
        VectorGet(_heap -> m_vector, sonIndex, &son);
        VectorGet(_heap -> m_vector, fatherIndex, &father);
        if ((_heap -> m_func)(son, father))
        {
            swap(_heap -> m_vector, sonIndex, fatherIndex);
        }
        else
        {
            break;
        }
        sonIndex = fatherIndex;
        fatherIndex = PARENT(sonIndex);
    }
}

const void* HeapPeek(const Heap* _heap)
{
    void *reValue;
    if (_heap == NULL)
    {
        return NULL;
    }
    VectorGet(_heap -> m_vector, _heap -> m_heapSize, &reValue);
    return reValue;
}


void* HeapExtract(Heap* _heap)
{
    void *reValue;
    if (_heap == NULL)
    {
        return NULL;
    }
    if (_heap -> m_heapSize <= 1)
    {
        VectorGet(_heap -> m_vector, _heap -> m_heapSize, &reValue);
        return reValue;
    }
    swap(_heap -> m_vector, _heap -> m_heapSize, 1);
    VectorRemove(_heap -> m_vector, &reValue);
    _heap -> m_heapSize--;
    heapify(_heap -> m_vector , _heap -> m_func);
    return reValue;
}

size_t HeapSize(const Heap* _heap)
{
    if (_heap == NULL)
    {
        return 0;
    }
    return _heap -> m_heapSize;
}



size_t HeapForEach(const Heap* _heap, ActionFunction _act, void* _context)
{
    size_t index = 0;
    if (_heap == NULL || _act == NULL || _context == NULL)
    {
        return 0;
    }
    if (_heap -> m_heapSize == 0)
    {
        return 0;
    }
    index = VectorForEach(_heap -> m_vector, _act, _context);
    return index;
}


static int CheckDupli(void *_element,size_t  ind,void *_context)
{
    if (_element == _context)
    {
        return 0;
    }
}



void HeapSort(Vector* _vec, LessThanComparator _pfLess)
{
    size_t index = VectorSize(_vec);
    void *first;
    void *last;
    if (_vec == NULL || _pfLess == NULL)
    {
        return;
    }
    while (index > 0)
    {
        VectorGet(_vec, 1, &first);
        VectorGet(_vec, index, &last);
        swap(_vec, 1, index);
        index--;
        SortHeapify(_vec, _pfLess, index);
    }
    return;
}




static void SortHeapify(Vector *_vector,  LessThanComparator _pfLess, int _index)
{
    size_t index = _index;
    void *left;
    void *right;
    void *father;
    if (index == 0)
    {
        return;
    }
    index = PARENT(index);
    while (index > 0)
    {
        VectorGet(_vector, LEFT(index), &left);
        VectorGet(_vector, index, &father);
        if (RIGHT(index) <= index)
        {
            VectorGet(_vector, index, &right);
            if (_pfLess(left, father))
            {
                swap(_vector, LEFT(index), index);
            }
            else
            {
                swap(_vector, RIGHT(index), index);
            }
        }
        else
        {
            if (_pfLess(left, father))
            {
                swap(_vector, LEFT(index), index);
            }
        }
        index--;
    }
}









