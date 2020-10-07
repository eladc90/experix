#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "vector.h"

void testBubble();
void testBuild();

struct  Heap
{
    Vector *m_vector;
    size_t m_heapSize;
};

int main()
{
    /* testBuild(); */
    testBubble();
}


void testBubble()
{
    Vector *vec; 
    vec = VectorCreate(10, 10);
    VectorAdd(vec, 8);
    VectorAdd(vec, 12);
    VectorAdd(vec, 5);
    VectorAdd(vec, 7); 
    bubbleSort(vec);
    VectorPrint(vec);
}
void testBuild()
{
    Vector *vec;
    Heap *heap;
    int a;
    vec = VectorCreate(10, 10);
    VectorAdd(vec, 1);
    VectorAdd(vec, 3);
    VectorAdd(vec, 5);
    VectorAdd(vec, 7);
    heap = HeapBuild(vec);
    HeapInsert(heap, 15);
    HeapPrint(heap);
}
