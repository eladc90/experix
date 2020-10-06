#include <stdio.h>
#include <stdlib.h>
#include "mu_test.h"
#include "../inclde/vector.h"

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
	HeapInsert(heap, &num);
	HeapInsert(heap, &num2);
	HeapInsert(heap, &num3);
	HeapInsert(heap, &num4);
	test = HeapPeek(heap); 
	ASSERT_THAT(test == &num4);
END_UNIT


UNIT(will_pass)
	ASSERT_THAT( sizeof(char) == 1);
	ASSERT_THAT( sizeof('A') == 4);
	ASSERT_THAT( sizeof(int) == 4);
END_UNIT

UNIT(will_fail)
	ASSERT_THAT( sizeof(int*) == 8);
END_UNIT


UNIT(malloc_zero_will_alloc_something)
	int *p = malloc(0);
	ASSERT_THAT(p != NULL);
END_UNIT




TEST_SUITE(framework test)
	TEST(will_pass)
	TEST(will_fail)
	TEST(testHeapPeek)	
	TEST(malloc_zero_will_alloc_something)
END_SUITE

