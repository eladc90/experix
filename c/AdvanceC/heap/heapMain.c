#include "heap.h"
#include "vector.h"
#include <stdio.h>
#include "../include/mu_test.h"
#define TRUE 1
#define FALSE 0



int LessThan(const void *_left, const void *_right);


int LessThan(const void *_left, const void *_right)
{
    return (*(int*)_left < *(int*)_right) ? TRUE : FALSE;
}


UNIT(testBulid)
	Heap* heap;
	int num = 37;
	int num2 = 18;
	int num3 = 29;
	int num4 = 110;
	Vector *vector;
	vector = VectorCreate(1, 3);
    heap = HeapBuild(vector, LessThan);
	ASSERT_THAT(heap != NULL);
	HeapDestroy(&heap);
END_UNIT

UNIT(testBulidNull)
	Heap* heap;
	int num = 37;
	int num2 = 18;
	int num3 = 29;
	int num4 = 110;
	Vector *vector;
	vector = VectorCreate(1, 3);
    heap = HeapBuild(NULL, LessThan);
	ASSERT_THAT(heap == NULL);
	HeapDestroy(&heap);
END_UNIT

UNIT(testBulidNull2)
	Heap* heap;
	int num = 37;
	int num2 = 18;
	int num3 = 29;
	int num4 = 110;
	Vector *vector;
	vector = VectorCreate(1, 3);
    heap = HeapBuild(NULL, NULL);
	vector = HeapDestroy(&heap);
	ASSERT_THAT(vector == NULL);
END_UNIT

UNIT(testDestroy)
	Heap* heap;
	int num = 37;
	int num2 = 18;
	int num3 = 29;
	int num4 = 110;
	Vector *vector;
	vector = VectorCreate(1, 3);
    heap = HeapBuild(vector, LessThan);
	HeapDestroy(&heap);
	HeapDestroy(&heap);
	ASSERT_THAT(heap == NULL);
END_UNIT

UNIT(testDestroy2)
	Heap* heap;
	int num = 37;
	int num2 = 18;
	int num3 = 29;
	int num4 = 110;
	Vector *vector;
	vector = VectorCreate(1, 3);
    heap = HeapBuild(vector, LessThan);
	vector = HeapDestroy(&heap);
	ASSERT_THAT(vector != NULL);
	HeapDestroy(&heap);
END_UNIT

UNIT(testInsert)
	Heap* heap;
	int num = 37;
	int num2 = 18;
	int num3 = 29;
	int num4 = 110;
	Vector *vector;
	vector = VectorCreate(1, 3);
    heap = HeapBuild(vector, LessThan);
	HeapInsert(heap, &num);
	HeapInsert(heap, &num2);
	HeapInsert(heap, &num3);
	HeapInsert(heap, &num4);
	ASSERT_THAT(heap != NULL);
	HeapDestroy(&heap);
END_UNIT

UNIT(testInsert2)
	Heap* heap;
	int num = 37;
	int num2 = 18;
	int num3 = 29;
	int num4 = 110;
	void *test;
	Vector *vector;
	vector = VectorCreate(2, 3);
    heap = HeapBuild(vector, LessThan);
	HeapInsert(heap, &num);
	HeapInsert(heap, &num2);
	HeapInsert(heap, &num3);
	HeapInsert(heap, &num4);
	
	HeapExtract(heap);
	HeapExtract(heap);
	
	test = HeapExtract(heap);
	ASSERT_THAT(test == &num3);
	HeapDestroy(&heap);
END_UNIT

UNIT(testInsert3)
	Heap* heap;
	HeapResult test;
	int num = 37;
	int num2 = 18;
	int num3 = 29;
	int num4 = 110;
	Vector *vector;
	vector = VectorCreate(3, 3);
    heap = HeapBuild(vector, LessThan);
	HeapInsert(heap, &num);
	HeapInsert(heap, &num2);
	HeapInsert(heap, &num3);
	HeapInsert(heap, &num4);
	test = HeapInsert(heap, &num4);
	ASSERT_THAT(test != HEAP_SUCCESS);
	HeapDestroy(&heap);
END_UNIT



UNIT(testHeapPeek)
	const void *test;
	Heap* heap;
	int num = 37;
	int num2 = 18;
	int num3 = 29;
	int num4 = 110;
	Vector *vector;
	vector = VectorCreate(1, 3);
	VectorAppend(vector, &num);
	VectorAppend(vector, &num2);
	VectorAppend(vector, &num3);
	VectorAppend(vector, &num4);
	heap = HeapBuild(vector, LessThan);
	test = HeapPeek(heap); 
	ASSERT_THAT(test == &num4);
	HeapDestroy(&heap);
END_UNIT




UNIT(testHeapExtract)
	const void *test;
	Heap* heap;
	int num = 37;
	int num2 = 18;
	int num3 = 29;
	int num4 = 110;
	Vector *vector;
	vector = VectorCreate(1, 3);
	VectorAppend(vector, &num);
	VectorAppend(vector, &num2);
	VectorAppend(vector, &num3);
	VectorAppend(vector, &num4);
	heap = HeapBuild(vector, LessThan);
	test = HeapExtract(heap); 
	test = HeapPeek(heap); 
	ASSERT_THAT(test == &num3);
	HeapDestroy(&heap);
END_UNIT


UNIT(testHeapExtract2)
	const void *test;
	Heap* heap;
	int num = 37;
	int num2 = 18;
	int num3 = 29;
	int num4 = 110;
	Vector *vector;
	vector = VectorCreate(1, 3);
	VectorAppend(vector, &num);
	VectorAppend(vector, &num2);
	VectorAppend(vector, &num3);
	VectorAppend(vector, &num4);
	heap = HeapBuild(vector, LessThan);
	test = HeapExtract(heap); 
	ASSERT_THAT(test == &num2);
	HeapDestroy(&heap);
END_UNIT

UNIT(testSort)
	Heap *heap;
	const void *test;
	int num = 37;
	int num2 = 18;
	int num3 = 29;
	int num4 = 110;
	Vector *vector;
	vector = VectorCreate(1, 3);
	VectorAppend(vector, &num);
	VectorAppend(vector, &num2);
	VectorAppend(vector, &num3);
	VectorAppend(vector, &num4);
	heap = HeapBuild(vector, LessThan);
	HeapSort(vector, LessThan);
	test =  HeapExtract(heap);
	ASSERT_THAT(test == &num4);
	HeapDestroy(&heap);
END_UNIT

UNIT(testSize)
	Heap *heap;
	const void *test;
	int num = 37;
	int num2 = 18;
	int num3 = 29;
	int num4 = 110;
	Vector *vector;
	vector = VectorCreate(1, 3);
	VectorAppend(vector, &num);
	VectorAppend(vector, &num2);
	VectorAppend(vector, &num3);
	VectorAppend(vector, &num4);
	heap = HeapBuild(vector, LessThan);
	HeapSort(vector, LessThan);
	test =  HeapSize(heap);
	ASSERT_THAT(test == 4);
	HeapDestroy(&heap);
END_UNIT


TEST_SUITE(framework test)
	TEST(testBulidNull)
	TEST(testBulidNull2)
	TEST(testHeapPeek)
	TEST(testDestroy2)
	TEST(testInsert)
	TEST(testInsert2)
	TEST(testInsert3)
	TEST(testHeapExtract)
	TEST(testHeapExtract2)
	TEST(testBulid)	
	TEST(testSort)
	TEST(testSize)
END_SUITE
