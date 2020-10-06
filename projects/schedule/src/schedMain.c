#include "Task.h"
#include "STS.h" 
#include "heap.h"
#include "vector.h" 
#include "timer.h" 
#include <stdio.h>
#include <stddef.h> /*size_t*/
#include <stdlib.h> /* malloc */





int OperationMult(void *arg);
int OperationRem(void *arg);
int OperationAdd(void *arg);





int main()
{
    int numberTest = 40;
    Scheduler* sche;
    sche = SchedulerCreate();
    SchedulerAddTask(sche, &numberTest, OperationMult, 7000);
    SchedulerAddTask(sche, &numberTest, OperationRem, 8000);
    SchedulerAddTask(sche, &numberTest, OperationAdd, 4500);
    SchedulerRun(sche);
    SchedulerDestroy(sche);
    return 0;
} 



int OperationAdd(void *arg)
{
    static int rounds = 3;
    int sum;
    sum = *(int*)(arg) + 10;
    printf("this is the add operation test: %d \n\n", sum); 
    if (rounds > 0)
    {
        rounds--;
        return 0;
    }
    return 1;
}


int OperationRem(void *arg)
{
    static int rounds = 3;
    int sum;
    sum = *(int*)(arg) - 10;
    printf("this is the subtraction operation test: %d \n\n", sum); 
    if (rounds > 0)
    {
        rounds--;
        return 0;
    }
    return 1;
}

int OperationMult(void *arg)
{
    static int rounds = 3;
    int sum;
    sum = *(int*)(arg) * 10;
    printf("this is the multiplication operation test: %d \n\n", sum); 
    if (rounds > 0)
    {
        rounds--;
        return 0;
    }
    return 1;
}











