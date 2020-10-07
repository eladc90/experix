#ifndef __MYMALLOC_H__
#define __MYMALLOC_H__

#include <stddef.h>

typedef struct Pool Pool;

typedef struct Node Node;

Pool *MyMallocCreate(size_t _sizeOfBuffer);

void MyMallocDestroy(Pool *_head);

void *MyMalloc(Pool *_pool, size_t _blockSize);

void Myfree(Pool *_pool , void *_adress);

#endif /* __MYMALLOC_H__ */
