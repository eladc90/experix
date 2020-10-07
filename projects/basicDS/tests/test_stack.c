#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "stack.h"
#include "test_h.h"

int testStackCreate1()
{
	int initialSize = 40;
	int extensionBlockSize = 5;
	Stack *test;
	test = StackCreate( extensionBlockSize, initialSize);
	if (test != NULL)
	{
		printf("yes""\n");
	}
}

int testStackCreate2()
{
	int initialSize = 0;
	int extensionBlockSize = 0;
	Stack *test;
	test = StackCreate( initialSize, extensionBlockSize);
	if (test == NULL)
	{
		printf("test 2 succeed (:" "\n");
	}
	else
	{
		printf("test 2 fail ):" "\n");
	}
}

int testStackCreate3()
{
	size_t initialSize = -1;
	size_t extensionBlockSize = 2;
	Stack *test;
	test = StackCreate( initialSize, extensionBlockSize);
	if (test == NULL)
	{
		printf("test 3 succeed (:" "\n");
	}
	else
	{
		printf("test 3 fail ):" "\n");
	}
}

int testStackDestroy()
{	
	int initialSize = 40;
	int extensionBlockSize = 5;
	Stack *test;
	test = StackCreate( extensionBlockSize, initialSize);
	StackDestroy (test);
	StackDestroy (test);
	printf("test 4 succeed (:" "\n");
}

/*
int testStackDestroy2()
{	
	int initialSize = 40;
	int extensionBlockSize = 5;
	Stack *test;
	test = NULL;
	if (StackDestroy(test) == NULL)
	{
		printf("test 5 succeed (:" "\n");
	}
	else
	{
		printf("test 5 fail ):" "\n");
	}
}
*/
int testStackPush()
{
	int item = 5;
	int item_2 = 6;
	int item_3 = 4;
	int initialSize = 2;
	int extensionBlockSize = 2;
	int extensionBlockSizeZero = 0;
	Stack *test;
	test = StackCreate( extensionBlockSize, initialSize);
	StackPush (test, item);
	StackPush (test, item_2);
	StackPush (test, item_3);



int testStackTop()
{
	int *ptr;
	int tempNum;
	int a;
	int item = 5;
	int item_2 = 6;
	int item_3 = 4;
	int initialSize = 2;
	int extensionBlockSize = 2;
	int extensionBlockSizeZero = 0;
	Stack *test;
	test = StackCreate( extensionBlockSize, initialSize);
	StackPush (test, item);
	StackPush (test, item_2);
	a = StackTop (test, ptr);

}
int main()
{
	testStackCreate1();
	testStackCreate2();
	testStackCreate3();
	testStackDestroy();
	/*testStackDestroy2();*/
	testStackPush();
	
}
