#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#define MAGIC_NUMBER 487232456

struct Vector 
{
	int * m_items; /* pointer to the first index of the array */
	size_t m_originalSize; /* the original allocated size of the vector*/
	size_t m_size; /* the actual allocated size of the vector in any given moment*/
	size_t m_nitems; /* the number of items inside the vector*/
	size_t m_blockSize; /* chunk size of the vector. any realloc get 2 of this*/
	size_t m_magicNumber; /* magic number to prevented re_free*/
};

/* test for VectorCreate function */

void Test1()
{
/* check if initialSize extensionBlockSize are zero */

	int initialSize = 0;
	int extensionBlockSize = 0;
	Vector *test;
	test = VectorCreate (initialSize, extensionBlockSize);
	if (test == NULL)
	{
		printf("test 1 succeed (:" "\n");
	}
	else
	{
		printf("test 1 fail ):" "\n");
	}
	free(test);

}

void Test2()
{
/* check if create a vector */
	int initialSize = 40;
	int extensionBlockSize = 5;
	Vector *test;
	test = VectorCreate (initialSize, extensionBlockSize);
	if (test != NULL)
	{
		printf("test 2 succeed (:" "\n");
	}
	else
	{
		printf("test 2 fail ):" "\n");
	}
/* test if initialized vector */	

	if (test -> m_originalSize == initialSize)
	{
		printf("test 3 succeed (:" "\n");
	}
	else
	{
		printf("test 3 fail ):" "\n");
	}

	if (test -> m_size == initialSize)
	{
		printf("test 4 succeed (:" "\n");
	}

	else
	{
		printf("test 4 fail ):" "\n");
	}
	if (test -> m_nitems == 0)
	{
		printf("test 5 succeed (:" "\n");
	}
	else
	{
		printf("test 5 fail ):" "\n");
	}
	if (test -> m_blockSize == extensionBlockSize)
	{
		printf("test 6 succeed (:" "\n");
	}
	else
	{
		printf("test 6 fail ):" "\n");
	}
	if (test -> m_magicNumber == MAGIC_NUMBER)
	{
		printf("test 7 succeed (:" "\n");
	}
	else
	{
		printf("test 7 fail ):" "\n");
	}
	free(test);
		
}

/* test for destroy function */

void Test3()
    {
/* check if destroy  */
	int initialSize = 40;
	int extensionBlockSize = 5;
	Vector *test;
	test = VectorCreate (initialSize, extensionBlockSize);
	VectorDestroy (test);
	if (test -> m_magicNumber == 0)
	{
		printf("test 8 succeed (:" "\n");
	}
	else
	{
		printf("test 8 fail ):" "\n");
	}
	free(test);
}

/*tests the add function */
 
void Test4()
{
/* check if vector == NULL */
	int item = 5;
	int initialSize = 40;
	int extensionBlockSize = 5;
	Vector *test;
	test = NULL;
	if (VectorAdd (test, item) == ERR_NULL)
	{
		printf("test 9 succeed (:" "\n");
	}
	else
	{
		printf("test 9 fail ):" "\n");
	}
}

void Test5()
{
/* checks if need to realloc */
	int item = 5;
	int item_2 = 6;
	int item_3 = 4;
	int initialSize = 2;
	int extensionBlockSize = 1;
	Vector *test;
	test = VectorCreate (initialSize, extensionBlockSize);
	VectorAdd (test, item);
	VectorAdd (test, item_2);
	VectorAdd (test, item_3);

/* check if size of array reallocated */ 

	if (test -> m_size == 3)
	{
		printf("test 10 succeed (:" "\n");
	}
	else
	{
		printf("test 10 fail ):" "\n");
	}
/* check if number of items updated */ 

	if (test -> m_nitems == 3)
	{
		printf("test 11 succeed (:" "\n");
	}
	else
	{
		printf("test 11 fail ):" "\n");
	}
/* check if OK */

	if (VectorAdd (test, item_3) == ERR_OK)
	{
		printf("test 12 succeed (:" "\n");
	}
	else
	{
		printf("test 12 fail ):" "\n");
	}
	free(test);
	
}

void Test6()
{
/* check overflow */ 
	int item = 5;
	int item_2 = 6;
	int item_3 = 4;
	int initialSize = 2;
	int extensionBlockSize = 0;
	Vector *test;
	test = VectorCreate (initialSize, extensionBlockSize);
	VectorAdd (test, item);
	VectorAdd (test, item_2);
	if (VectorAdd (test, item_3) == ERR_OVERFLOW)
	{
		printf("test 13 succeed (:" "\n");
	}
	else
	{
		printf("test 13 fail ):" "\n");
	}
	free(test);
}

/*tests the delete function */

void Test7()
{
/* check if *items is NULL */
	Vector *test;
	int *item;
	int initialSize = 2;
	int extensionBlockSize = 2;
	test = VectorCreate (initialSize, extensionBlockSize);
	item = NULL;
	if (VectorDelete (test, item) == ERR_NULL)
	{
		printf("test 14 succeed (:" "\n");
	}
	else
	{
		printf("test 14 fail ):" "\n");
	}
	free(test);	
}

void Test8()
{
/* check if *vector is NULL */
	Vector *test;
	int item_1 = 5;
	int *item;
	int initialSize = 2;
	int extensionBlockSize = 2;
	test = NULL;
	item = &item_1;
	if (VectorDelete (test, item) == ERR_NULL)
	{
		printf("test 15 succeed (:" "\n");
	}
	else
	{
		printf("test 15 fail ):" "\n");
	}

}
void Test9()
{
/* check if get underflow */
	Vector *test;
	int item_1 = 5;
	int *item;
	int initialSize = 2;
	int extensionBlockSize = 2;
	test = VectorCreate (initialSize, extensionBlockSize);
	item = &item_1;
	if (VectorDelete (test, item) == ERR_UNDERFLOW)
	{
		printf("test 16 succeed (:" "\n");
	}
	else
	{
		printf("test 16 fail ):" "\n");
	}
	free(test);
}	
void Test10()
{
/* check if return the value deleted, if number of items down by one and if return err_ok*/
	int deletItem;
	int *item = &deletItem;
	int item_1 = 5;
	int item_2 = 6;
	int item_3 = 8;
	int initialSize = 2;
	int extensionBlockSize = 1;
	Vector *test;
	test = VectorCreate (initialSize, extensionBlockSize);
	VectorAdd (test, item_1);
	VectorAdd (test, item_2);
	VectorAdd (test, item_3);
	VectorDelete (test, item);
	if (*item == item_3)
	{
		printf("test 17 succeed (:" "\n");
	}
	else
	{
		printf("test 17 fail ):" "\n");
	}
	if (test -> m_nitems == 2)
	{
		printf("test 18 succeed (:" "\n");
	}
	else
	{
		printf("test 18 fail ):" "\n");
	}
	if (VectorDelete (test, item) == ERR_OK)
	{
		printf("test 19 succeed (:" "\n");
	}
	else
	{
		printf("test 19 fail ):" "\n");
	}
	free(test);
}

/*tests the VectorGet function */

void Test11()
{
/* check if Vector NULL */
	int index = 2;
	int getItem;
	int *item = &getItem;
	int item_1 = 5;
	int item_2 = 6;
	int item_3 = 8;
	int initialSize = 2;
	int extensionBlockSize = 1;
	Vector *test;
	test = NULL;
	VectorAdd (test, item_1);
	VectorAdd (test, item_2);
	VectorAdd (test, item_3);
	if (VectorGet (test, index, item) == ERR_NULL)
	{
		printf("test 20 succeed (:" "\n");
	}
	else
	{
		printf("test 20 fail ):" "\n");
	}
}

void Test12()
{
/* check if item pointer == NULL */
	int index = 2;
	int getItem;
	int *item = NULL;
	int item_1 = 5;
	int item_2 = 6;
	int item_3 = 8;
	int initialSize = 2;
	int extensionBlockSize = 1;
	Vector *test;
	test = VectorCreate (initialSize, extensionBlockSize);
	VectorAdd (test, item_1);
	VectorAdd (test, item_2);
	VectorAdd (test, item_3);
	if (VectorGet (test, index, item) == ERR_NULL)
	{
		printf("test 21 succeed (:" "\n");
	}
	else
	{
		printf("test 21 fail ):" "\n");
	}
	free(test);
}

void Test13()
{
/* check if index is less than 0 */

	int index = -2;
	int getItem;
	int *item = &getItem;
	int item_1 = 5;
	int item_2 = 6;
	int item_3 = 8;
	int initialSize = 2;
	int extensionBlockSize = 1;
	Vector *test;
	test = VectorCreate (initialSize, extensionBlockSize);
	VectorAdd (test, item_1);
	VectorAdd (test, item_2);
	VectorAdd (test, item_3);
	if (VectorGet (test, index, item) == ERR_INVALID_INPUT)
	{
		printf("test 22 succeed (:" "\n");
	}
	else
	{
		printf("test 22 fail ):" "\n");
	}
	free(test);
}

void Test14()
{
/* check if index is more than number of items */
	int index = 4;
	int getItem;
	int *item = &getItem;
	int item_1 = 5;
	int item_2 = 6;
	int item_3 = 8;
	int initialSize = 2;
	int extensionBlockSize = 1;
	Vector *test;
	test = VectorCreate (initialSize, extensionBlockSize);
	VectorAdd (test, item_1);
	VectorAdd (test, item_2);
	VectorAdd (test, item_3);
	if (VectorGet (test, index, item) == ERR_INVALID_INPUT)
	{
		printf("test 23 succeed (:" "\n");
	}
	else
	{
		printf("test 23 fail ):" "\n");
	}
	free(test);
}

void Test15()
{
/* check if ok and retunt the value */
	int index = 1;
	int getItem;
	int *item = &getItem;
	int item_1 = 5;
	int item_2 = 6;
	int item_3 = 8;
	int initialSize = 2;
	int extensionBlockSize = 1;
	Vector *test;
	test = VectorCreate (initialSize, extensionBlockSize);
	VectorAdd (test, item_1);
	VectorAdd (test, item_2);
	VectorAdd (test, item_3);
	VectorGet (test, index, item);
	if (getItem == 6)
	{
		printf("test 24 succeed (:" "\n");
	}
	else
	{
		printf("test 24 fail ):" "\n");
	}
	if (VectorGet (test, index, item) == ERR_OK)
	{
		printf("test 25 succeed (:" "\n");
	}
	else
	{
		printf("test 25 fail ):" "\n");
	}
	free(test);
	
}

/* tests the VectorSet function */

void Test16()
{
/* check if vector is NULL */
	int index = 2;
	int checkItem = 7;
	int item_1 = 5;
	int item_2 = 6;
	int item_3 = 8;
	int initialSize = 2;
	int extensionBlockSize = 1;
	Vector *test;
	test = NULL;
	if (VectorSet (test, index, checkItem) == ERR_NULL)
	{
		printf("test 26 succeed (:" "\n");
	}
	else
	{
		printf("test 26 fail ):" "\n");
	}
}
void Test17()
{
/* check index value, 2 errors and 1 OK */
	
	int index = -2;
	int secIndex = 4;
	int okIndex = 1;
	int checkItem = 7;
	int item_1 = 5;
	int item_2 = 6;
	int item_3 = 8;
	int initialSize = 2;
	int extensionBlockSize = 1;
	Vector *test;
	test = VectorCreate (initialSize, extensionBlockSize);
	VectorAdd (test, item_1);
	VectorAdd (test, item_2);
	VectorAdd (test, item_3);
	if (VectorSet (test, index, checkItem) == ERR_INVALID_INPUT)
	{
		printf("test 27 succeed (:" "\n");
	}
	else
	{
		printf("test 27 fail ):" "\n");
	}
	if (VectorSet (test, secIndex, checkItem) == ERR_INVALID_INPUT)
	{
		printf("test 28 succeed (:" "\n");
	}
	else
	{
		printf("test 28 fail ):" "\n");
	}
	if (VectorSet (test, okIndex, checkItem) == ERR_OK)
	{
		printf("test 29 succeed (:" "\n");
	}
	else
	{
		printf("test 29 fail ):" "\n");
	}
	VectorSet (test, okIndex, checkItem);
	if (test -> m_items [okIndex] == 7)
	{
		printf("test 30 succeed (:" "\n");
	}
	else
	{
		printf("test 30 fail ):" "\n");
	}
	free(test);
}

/* tests the VectorItemsNum function */

void Test18()
{
/* check if vector NULL if ptr NULL and if OK*/
	int numOfItems;
	int *nllPtr;
	int *ptrToItems;
	int checkItem = 7;
	int item_1 = 5;
	int item_2 = 6;
	int item_3 = 8;
	int initialSize = 2;
	int extensionBlockSize = 1;
	Vector *test;
	Vector *testNull;
	nllPtr = NULL;
	testNull = NULL;
	ptrToItems = &numOfItems;
	test = VectorCreate (initialSize, extensionBlockSize);
	VectorAdd (test, item_1);
	VectorAdd (test, item_2);
	VectorAdd (test, item_3);
	
	
	if (VectorItemsNum (testNull, ptrToItems) == ERR_NULL)
	{
		printf("test 31 succeed (:" "\n");
	}
	else
	{
		printf("test 31 fail ):" "\n");
	}
	
	if (VectorItemsNum (test, nllPtr) == ERR_NULL)
	{
		printf("test 32 succeed (:" "\n");
	}
	else
	{
		printf("test 32 fail ):" "\n");
	}
	free(test);

}

void Test19()
{
/* check if vector NULL if ptr NULL and if OK*/
	Vector *test;
	int numOfItems;
	int *ptrToItems;
	int checkItem = 7;
	int item_1 = 5;
	int item_2 = 6;
	int item_3 = 3;
	int initialSize = 2;
	int extensionBlockSize = 1;
	test = VectorCreate (initialSize, extensionBlockSize);
	ptrToItems = &numOfItems;
	VectorAdd (test, item_1);
	VectorAdd (test, item_2);
	VectorAdd (test, item_3);
	VectorItemsNum (test, ptrToItems);
	if (numOfItems == 3)
	{
		printf("test 33 succeed (:" "\n");
	}
	else
	{
		printf("test 33 fail ):" "\n");
	}
	if (VectorItemsNum (test, ptrToItems) == ERR_OK)
	{
		printf("test 34 succeed (:" "\n");
	}
	else
	{
		printf("test 34 fail ):" "\n");
	}
	free(test);
	
}

/* tests the VectorPrint function */

void Test20()
{
	Vector *test;
	int a;
	int checkItem = 7;
	int item_1 = 5;
	int item_2 = 8;
	int item_3 = 4;
	int initialSize = 2;
	int extensionBlockSize = 1;
	test = VectorCreate (initialSize, extensionBlockSize);
	VectorAdd (test, item_1);
	VectorAdd (test, item_2);
	VectorAdd (test, item_3);
	printf("array in vector is: ");
	VectorPrint(test);
	free(test);
}


int main()
{
	Test1();
	Test2();	
	Test3();
	Test4();
	Test5();
	Test6();	
	Test7();
	Test8();
	Test9();
	Test10();	
	Test11();
	Test12();
	Test13();
	Test14();	
	Test15();
	Test16();
	Test17();
	Test18();	
	Test19();
	Test20();
}

