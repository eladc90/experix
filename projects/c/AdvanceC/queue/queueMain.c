#include "../include/queue.h"
#include <stdlib.h>
#include <stdio.h>




void testQueueCreate();

void testQueueDestroy();
void testQueueDestroy2();
void testQueueDestroy3();

void testQueueEnqueue();
void testQueueEnqueue2();
void testQueueEnqueue3();

void testQueueDequeue();
void testQueueDequeue2();

void testQueueIsEmpty();
void testQueueIsEmpty3();
void testQueueIsEmpty2();

void testForEach();

int main()
{
	testQueueCreate();

	testQueueDestroy();
	testQueueDestroy2();
	testQueueDestroy3();

	testQueueEnqueue();
	testQueueEnqueue2();
	testQueueEnqueue3();

	testQueueDequeue();
	testQueueDequeue2();

	testQueueIsEmpty();
	testQueueIsEmpty3();
	testQueueIsEmpty2();

	testForEach();
    return 0;
}

/******************************************/

void elementDestroy(void* _item)
{
	if (_item != NULL)
	{
		free( _item);
	}
	return;
}

void testQueueCreate()
{
	Queue *Q = NULL;
	Q = QueueCreate(10);
	printf("%-15s","CreateQ1: ");
	if( Q == NULL)
	{
		printf("Failed\n");
	}
	else
	{
		printf("Pass\n");
	}
	QueueDestroy(&Q,NULL);
}

void testQueueDestroy()
{
	Queue *Q =NULL;
	Q = QueueCreate(10);
	QueueDestroy(&Q,NULL);
	printf("%-15s","DestroyQ1: ");

	if( Q == NULL)
	{
		printf("Failed\n");
	}
	else
	{
		printf("Pass\n");
	}
	return;
}


void testQueueDestroy2()
{
	Queue *Q = NULL;
	Q = QueueCreate(10);
	QueueDestroy(NULL,NULL);
	printf("%-15s","DestroyQ2: ");

	if(Q == NULL)
	{
		printf("Failed\n");
	}
	else
	{
		printf("Pass\n");
	}
	return;
}




/* void testQueueDestroy3()
{
	int index = 0;
	Queue *queue;
	int **arr;
	queue = QueueCreate(10);
	if (arr != NULL)
	{
		for (; index < 5; index++)
		{
			arr = (int **) malloc (sizeof(int ) * 5);
			QueueEnqueue(queue, &arr);
		}
	}
	QueueDestroy(&queue, elementDestroy);
	if (queue == NULL)
	{
		printf("list Destroy test 3: pass \n");
	}
	else
	{
		printf("list Destroy test 3: fail \n");
	}
} */


void testQueueDestroy3()
{
	int index = 0;
	Queue *queue;
	int *ptr;
	queue = QueueCreate(10);
	for (; index < 5; index++)
	{
		ptr = (int *) malloc (sizeof(int) * 5);
		QueueEnqueue(queue, ptr);
	}
	QueueDestroy(&queue, elementDestroy);
	if (queue == NULL)
	{
		printf("list Destroy test 3: pass \n");
	}
	else
	{
		printf("list Destroy test 3: fail \n");
	}
}

void testQueueEnqueue()
{
	int status;
	Queue *queue;
	queue = QueueCreate(10);
	status = QueueEnqueue(NULL, NULL);
	if (status == QUEUE_NULL_ERR)
	{
		printf("queue en test 1: pass \n");
	}
	else
	{
		printf("queue en test 1: fail \n");
	}
	QueueDestroy(&queue, NULL);
}


void testQueueEnqueue2()
{
	int status;
	Queue *queue;
	int num = 12;
	int num2 = 54;
	int num3 = 5;
	queue = QueueCreate(3);
	status = QueueEnqueue(queue, &num);
	status = QueueEnqueue(queue, &num2);
	status = QueueEnqueue(queue, &num3);
	status = QueueEnqueue(queue, &num);
	if (status == QUEUE_OVERFLOW)
	{
		printf("queue en test 2: pass \n");
	}
	else
	{
		printf("queue en test 2: fail \n");
	}
	QueueDestroy(&queue, NULL);
}

void testQueueEnqueue3()
{
	void *status;
	Queue *queue;
	int num = 12;
	int num2 = 54;
	int num3 = 5;
	queue = QueueCreate(3);
	QueueEnqueue(queue, &num);
	QueueEnqueue(queue, &num2);
	QueueEnqueue(queue, &num3);
	QueueDequeue(queue, &status);
	if (status == &num)
	{
		printf("queue en test 3: pass \n");
	}
	else
	{
		printf("queue en test 3 fail \n");
	}
	QueueDestroy(&queue, NULL);
}

void testQueueDequeue()
{
	void *test;
	int status;
	Queue *queue;
	int num = 12;
	int num2 = 54;
	int num3 = 5;
	queue = QueueCreate(3);
	QueueEnqueue(queue, &num);
	QueueEnqueue(queue, &num2);
	QueueEnqueue(queue, &num3);
	status = QueueDequeue(queue, &test);
	if (status == QUEUE_SUCCESS)
	{
		printf("queue de test 1: pass \n");
	}
	else
	{
		printf("queue de test 1 fail \n");
	}
	QueueDestroy(&queue, NULL);
}

void testQueueDequeue2()
{
	void *test;
	int status;
	Queue *queue;
	queue = QueueCreate(3);
	status = QueueDequeue(queue, &test);
	if (status == QUEUE_UNDERFLOW)
	{
		printf("queue en test 2: pass \n");
	}
	else
	{
		printf("queue en test 2fail \n");
	}
	QueueDestroy(&queue, NULL);
}

void testQueueIsEmpty()
{
	int status;
	Queue *queue;
	int num = 12;
	int num2 = 54;
	int num3 = 5;
	queue = QueueCreate(3);
	QueueEnqueue(queue, &num);
	QueueEnqueue(queue, &num2);
	QueueEnqueue(queue, &num3);
	status = QueueIsEmpty(queue);
	if (status == 0)
	{
		printf("queue en test 1: pass \n");
	}
	else
	{
		printf("queue en test 1 fail \n");
	}
}


void testQueueIsEmpty2()
{
	int status;
	Queue *queue;
	queue = QueueCreate(3);
	status = QueueIsEmpty(queue);
	if (status == 1)
	{
		printf("queue en test 2: pass \n");
	}
	else
	{
		printf("queue en test 2 fail \n");
	}
}

void testQueueIsEmpty3()
{
	int status;
	Queue *queue;
	queue = NULL;
	status = QueueIsEmpty(queue);
	if (status == 0)
	{
		printf("queue en test 3: pass \n");
	}
	else
	{
		printf("queue en test 3 fail \n");
	}
}

int action(void* _num , size_t _index , void* _item)
{
	if (_num == _item)
	{
		return 0;
	}
	return 1;
}

void testForEach()
{
	size_t status;
	Queue *queue;
	int num = 548;
	int num2 = 24;
	int num3 = 55;
	queue = QueueCreate(3);
	QueueEnqueue(queue, &num);
	QueueEnqueue(queue, &num2);
	QueueEnqueue(queue, &num3);
	status = QueueForEach(queue, action, &num2);
	if (status == 1)
	{
		printf("For Each test 1: pass \n");
	}
	else
	{
		printf("For Each test 1 fail \n");
	}
}



