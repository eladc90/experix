#include <stdio.h>
#include "vector.h"
#include <stdlib.h>

int action(void* _num , size_t _index , void* _item);

static void elementDestroy(void* _item);

void testVectorCreate(); /* check normal create and create with 0 and 0 */

void testVectorDestroy();
void testVectorDestroy2();
void testVectorDestroy3();

void testVectorDelete();

void testVectorAppend(); /* check normal append */
void testVectorAppend2(); /* check overflow and NULL */
void testVectorAppend3(); /* check for need realloc */
void testVectorAppend4(); /* check for multiple  appends */
void testVectorAppend5(); /* check vector size update */

void testVectorRemove(); /* check for vector null */
void testVectorRemove2(); /* check for remove empty vector */
void testVectorRemove3(); /* checks for muliple remove */

void testVectorGet(); /* check if get the right item */
void testVectorGet2(); /* check if vector NULL */
void testVectorGet3(); /* check for invalid index */


void testVectorSet(); 
void testVectorSet2(); 
void testVectorSet3(); /* check for vector NULL */
void testVectorSet4(); /* check for invalid index */

void testVectorSize(); /* check for the Size */
void testVectorSize2(); /* check size with NULL */

void testVectorCapacity(); 




int main()
{
	testVectorCreate();

	testVectorAppend();
	testVectorAppend2();
	testVectorAppend3();
	testVectorAppend4();
	testVectorAppend5();

	testVectorDestroy();
	testVectorDestroy2();
	testVectorDestroy3();

	testVectorRemove(); 
	testVectorRemove2();
	testVectorRemove3();

	testVectorGet();
	testVectorGet2();
	testVectorGet3();

	testVectorSet();
	testVectorSet2(); 
	testVectorSet3(); 
	testVectorSet4();

	testVectorSize();
	testVectorSize2();

	testVectorCapacity();



	return 0;
}

void testVectorCreate()
{
	Vector *vector;
	vector = VectorCreate(10, 10);
	if (vector != NULL)
	{
		printf("vector create test 1: pass \n");
	}
	else
	{
		printf("vector create test 1: fail \n");
	}
	vector = VectorCreate(0, 0);
	if (vector == NULL)
	{
		printf("vector create test 2: pass \n");
	}
	else
	{
		printf("vector create test 2: fail \n");
	}
	VectorDestroy(&vector, NULL);
}

void elementDestroy(void* _item)
{
	if (_item != NULL)
	{
		free( _item);
	}
	return;
}

void testVectorDestroy()
{
	Vector *vector;
	vector = VectorCreate(10, 10);
	VectorDestroy (&vector, elementDestroy);
	VectorDestroy (&vector, elementDestroy);
	printf("vector destroy test 1: pass \n");
}

void testVectorDestroy2()
{
	Vector *vector;
	vector = NULL;
	VectorDestroy (&vector, NULL);
	printf("vector destroy test 2: pass \n");
	
}

void testVectorDestroy3()
{
	Vector *vector;
	int i, *ptr;
	vector = VectorCreate(10, 10);
	if (vector != NULL)
	{
		for (i = 0; i < 5; i++)
		{
			ptr = (int*)malloc(sizeof(int));
			VectorAppend(vector, ptr);
		}
	}
	VectorDestroy (&vector, elementDestroy);
	printf("vector destroy test 3: pass \n");
	
}




void testVectorAppend()
{
	void *test;
	int status;
	int num = 7;
	Vector *vector;
	vector = VectorCreate(10, 10);
	status = VectorAppend (vector, &num);
	if (status == VECTOR_SUCCESS)
	{
		printf("vector append test 1: pass \n");
	}
	else
	{
		printf("vector append test 1: fail \n");
	}
	VectorRemove(vector, &test);
	if (test == &num)
	{
		printf("vector append test 2: pass \n");
	}
	else
	{
		printf("vector append test 2: fail \n");
	}
	VectorDestroy(&vector, NULL);

}

void testVectorAppend2()
{
	int status;
	int num = 7;
	Vector *vector;
	vector = NULL;
	status = VectorAppend(vector, &num);
	if (status == VECTOR_NULL)
	{
		printf("vector append 2 test 1: pass \n");
	}
	else
	{
		printf("vector append 2 test 1: fail \n");
	}
	vector = VectorCreate(1, 0);
	VectorAppend(vector, &num);
	status = VectorAppend(vector, &num);
	if (status == VECTOR_OVERFLOW)
	{
		printf("vector append 2 test 2: pass \n");
	}
	else
	{
		printf("vector append 2 test 2: fail \n");	
	}
	VectorDestroy(&vector, NULL);
}


void testVectorAppend3()
{
	int status;
	int num = 7;
	int num2 = 8;
	Vector *vector;
	vector = VectorCreate(1, 1);
	VectorAppend(vector, &num);
	status = VectorAppend(vector, &num2);
	if (status == VECTOR_SUCCESS)
	{
		printf("vector append 3 test 1: pass \n");
	}
	else
	{
		printf("vector append 3 test 1: fail \n");	
	}
	VectorDestroy(&vector, NULL);
}

void testVectorAppend4()
{
	void *test;
	int status;
	int num = 7;
	int num2 = 8;
	Vector *vector;
	vector = VectorCreate(1, 1);
	VectorAppend(vector, &num);
	status = VectorAppend(vector, &num2);
	if (status == VECTOR_SUCCESS)
	{
		printf("vector append 4 test 1: pass \n");
	}
	else
	{
		printf("vector append 4 test 1: fail \n");	
	}
	VectorRemove(vector, &test);
	if (test == &num2)
	{
		printf("vector append 4 test 2: pass \n");
	}
	else
	{
		printf("vector append 4 test 2: fail \n");
	}
	VectorRemove(vector, &test);
	if (test == &num)
	{
		printf("vector append 4 test 3: pass \n");
	}
	else
	{
		printf("vector append 4 test 3: fail \n");
	}
	VectorDestroy(&vector, NULL);
}


void testVectorAppend5()
{
	int status;
	int num = 7;
	int num2 = 8;
	Vector *vector;
	vector = VectorCreate(1, 1);
	VectorAppend(vector, &num);
	VectorAppend(vector, &num2);
	status = VectorSize(vector);
	if (status == 2)
	{
		printf("vector append 5 test 4: pass \n");
	}
	else
	{
		printf("vector append 5 test 4: fail \n");	
	}
	VectorDestroy(&vector, NULL);
}


void testVectorRemove()
{
	void *test;
	int status;
	Vector *vector;
	vector = NULL;
	status = VectorRemove (vector, &test);
	if (status == VECTOR_NULL)
	{
		printf("vector remove 1 test 1: pass \n");
	}
	else
	{
		printf("vector remove 1 test 1: fail \n");	
	}
	vector = VectorCreate(10, 1);
	status = VectorRemove (vector, &test);
	VectorDestroy(&vector, NULL);
}

void testVectorRemove2()
{
	void *test;
	int status;
	Vector *vector;
	vector = VectorCreate(10, 1);
	status = VectorRemove (vector, &test);
	if (status == VECTOR_UNDERFLOW)
	{
		printf("vector remove 2 test 1: pass \n");
	}
	else
	{
		printf("vector remove 2 test 1: fail \n");	
	}
	VectorDestroy(&vector, NULL);
}


void testVectorRemove3()
{
	void *test;
	int num = 7;
	int num2 = 8;
	int num3 = 9;
	int num4 = 10;
	Vector *vector;
	vector = VectorCreate(10, 1);
	VectorAppend(vector, &num);
	VectorAppend(vector, &num2);
	VectorAppend(vector, &num3);
	VectorAppend(vector, &num4);
	VectorRemove (vector, &test);
	if (test == &num4)
	{
		printf("vector remove 3 test 1: pass \n");
	}
	else
	{
		printf("vector remove 3 test 1: fail \n");	
	}
	VectorRemove (vector, &test);
	if (VectorSize(vector) == 2)
	{
		printf("vector remove 3 test 2: pass \n");
	}
	else
	{
		printf("vector remove 3 test 2: fail \n");	
	}
	VectorDestroy(&vector, NULL);
}

Vector_Result VectorGet(const Vector* _vector, size_t _index, void** _pValue);


void testVectorGet()
{
	void *test;
	int num = 7;
	int num2 = 8;
	int num3 = 9;
	int num4 = 10;
	Vector *vector;
	vector = VectorCreate(10, 1);
	VectorAppend(vector, &num);
	VectorAppend(vector, &num2);
	VectorAppend(vector, &num3);
	VectorAppend(vector, &num4);
	VectorGet(vector, 3, &test);
	if (test == &num3)
	{
		printf("vector Get 1 test 1: pass \n");
	}
	else
	{
		printf("vector Get 1 test 1: fail \n");	
	}
	VectorGet(vector, 4, &test);
	if (test == &num4)
	{
		printf("vector Get 1 test 2: pass \n");
	}
	else
	{
		printf("vector Get 1 test 2: fail \n");	
	}
	VectorDestroy(&vector, NULL);
}

void testVectorGet2()
{
	void *test;
	int status;
	Vector *vector;
	vector = NULL;
	status = VectorGet (vector, 1, &test);
	if (status == VECTOR_NULL)
	{
		printf("vector Get 2 test 1: pass \n");
	}
	else
	{
		printf("vector Get 2 test 1: fail \n");	
	}
}

Vector_Result VectorGet(const Vector* _vector, size_t _index, void** _pValue);

void testVectorGet3()
{
	int status;
	void *test;
	int num = 7;
	int num2 = 8;
	int num3 = 9;
	int num4 = 10;
	Vector *vector;
	vector = VectorCreate(10, 1);
	VectorAppend(vector, &num);
	VectorAppend(vector, &num2);
	VectorAppend(vector, &num3);
	VectorAppend(vector, &num4);
	status = VectorGet(vector, 5, &test);
	if (status == VECTOR_INDEX_OUT_OF_BOUNDS_ERROR)
	{
		printf("vector Get 3 test 1: pass \n");
	}
	else
	{
		printf("vector Get 3 test 1: fail \n");	
	}
	VectorDestroy(&vector, NULL);
}


void testVectorSet()
{
	int status;
	int num = 7;
	int num2 = 8;
	int num3 = 9;
	int num4 = 10;
	Vector *vector;
	vector = VectorCreate(10, 1);
	VectorAppend(vector, &num);
	VectorAppend(vector, &num2);
	VectorAppend(vector, &num3);
	status = VectorSet(vector, 3, &num4);
	if (status == VECTOR_SUCCESS)
	{
		printf("vector Set 1 test 1: pass \n");
	}
	else
	{
		printf("vector Set 1 test 1: fail \n");	
	}
	VectorDestroy(&vector, NULL);
}

void testVectorSet2()
{
	void *test;
	int num = 7;
	int num2 = 8;
	int num3 = 9;
	int num4 = 10;
	Vector *vector;
	vector = VectorCreate(10, 1);
	VectorAppend(vector, &num);
	VectorAppend(vector, &num2);
	VectorAppend(vector, &num3);
	VectorSet(vector, 3, &num4);
	VectorGet(vector, 3, &test);
	if (test == &num4)
	{
		printf("vector Set 2 test 1: pass \n");
	}
	else
	{
		printf("vector Set 2 test 1: fail \n");	
	}
	VectorDestroy(&vector, NULL);
}


void testVectorSet3()
{
	int status;
	Vector *vector;
	int num4 = 29;
	vector = NULL;
	status = VectorSet(vector, 2, &num4);
	if (status == VECTOR_NULL)
	{
		printf("vector Set 3 test 1: pass \n");
	}
	else
	{
		printf("vector Set 3 test 1: fail \n");	
	}
}

void testVectorSet4()
{
	int status;
	int num = 7;
	int num2 = 8;
	int num3 = 9;
	int num4 = 10;
	Vector *vector;
	vector = VectorCreate(10, 1);
	VectorAppend(vector, &num);
	VectorAppend(vector, &num2);
	VectorAppend(vector, &num3);
	status = VectorSet(vector, 5, &num4);
	if (status == VECTOR_INDEX_OUT_OF_BOUNDS_ERROR)
	{
		printf("vector Set 4 test 1: pass \n");
	}
	else
	{
		printf("vector Set 4 test 1: fail \n");	
	}
	VectorDestroy(&vector, NULL);
}

/* size_t VectorSize(const Vector* _vector) */

void testVectorSize()
{
	size_t size;
	int num = 7;
	int num2 = 8;
	int num3 = 9;
	int num4 = 10;
	Vector *vector;
	vector = VectorCreate(10, 1);
	VectorAppend(vector, &num);
	VectorAppend(vector, &num2);
	VectorAppend(vector, &num3);
	VectorAppend(vector, &num4);
	size = VectorSize(vector);
	if (size == 4)
	{
		printf("vector Size 1 test 1: pass \n");
	}
	else
	{
		printf("vector Size 1 test 1: fail \n");	
	}
	VectorDestroy(&vector, NULL);
}

void testVectorSize2()
{
	size_t size;
	size = VectorSize(NULL);
	if (size == 0)
	{
		printf("vector Size 2 test 1: pass \n");
	}
	else
	{
		printf("vector Size 2 test 1: fail \n");	
	}
}

size_t VectorCapacity(const Vector* _vector);

void testVectorCapacity()
{
	size_t size;
	int num = 7;
	int num2 = 8;
	int num3 = 9;
	int num4 = 10;
	Vector *vector;
	vector = VectorCreate(1, 3);
	VectorAppend(vector, &num);
	VectorAppend(vector, &num2);
	VectorAppend(vector, &num3);
	VectorAppend(vector, &num4);
	size = VectorCapacity(vector);
	if (size == 4)
	{
		printf("vector Capacity 1 test 1: pass \n");
	}
	else
	{
		printf("vector Capacity 1 test 1: fail \n");	
	}
	VectorDestroy(&vector, NULL);
}


int action(void* _num , size_t _index , void* _item)
{

	if (_num == _item)
	{
		return 0;
	}
	return 1;
}










