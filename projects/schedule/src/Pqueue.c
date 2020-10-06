#include "heap.h"
#include "vector.h"
#include "Pqueue.h"
#include "timer.h"
#include <stdlib.h>
#define INIT_NUM_OF_TASKS 10

struct Pqueue
{
    Heap *m_heap;
};


Pqueue* PqeueuCreate()
{
    Pqueue *Pqeueu = NULL;
    Vector *vec = NULL;
    Heap *heap = NULL;
    vec = VectorCreate(INIT_NUM_OF_TASKS, INIT_NUM_OF_TASKS);
    if (vec == NULL)
    {
        return NULL;
    }
    heap = HeapBuild(vec, TimeCompareLess);
    if (heap == NULL)
    {
        free(vec);
        return NULL;
    }
    Pqeueu = (Pqueue *) malloc (sizeof (Pqueue));
    if (Pqeueu == NULL)
    {
        free(heap);
        free(vec);
        return NULL;
    }
    Pqeueu -> m_heap = heap;
    return Pqeueu;
}


int PqueueInsert(Pqueue *_pqueue, void *_element)
{
    int status;
    status = HeapInsert(_pqueue -> m_heap, _element);
    return status;
}


void *PqueueExtract(Pqueue *_pqueue)
{
    void *item;
    item = HeapExtract(_pqueue -> m_heap);
    return item;
}

void PqueueDesroy(Pqueue *_pqueue, void (*_elementDestroy) (void*))
{
    Vector *vec;
    Heap *heap = _pqueue -> m_heap;
    vec = HeapDestroy(&heap);
    VectorDestroy(&vec, _elementDestroy);
    free(_pqueue);
    return;
}
