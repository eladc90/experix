#include <pthread.h>
#include <stdio.h>
#define NUM_OF_THREADS 50

void *PrintFunc(void *_index);



int main()
{
	int arr[NUM_OF_THREADS] = {0};
	int index = 0;
	int status = 0;
	pthread_t threads[NUM_OF_THREADS];
	for (index = 0; index < NUM_OF_THREADS; index++)
	{
		arr[index] = index;
	}
	for (index = 0; index < NUM_OF_THREADS; index++)
	{
		pthread_create(&threads[index], NULL, PrintFunc, (void *) &arr[index]);
	}
	for (index = 0; index < NUM_OF_THREADS; index++)
	{
		pthread_join(threads[index], NULL);
	}
	
	
}

void *PrintFunc(void *_index)
{
	printf("this is the index: %d\n", (*(int *) _index));
	sleep(1);
	pthread_exit(NULL);
}

