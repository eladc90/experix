#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "iter.h"


int action(void* _num, void* _item)
{

	if (_num == _item)
	{
		return 0;
	}
	return 0;
}

void testListItrFindFirst();

int main()
{
    testListItrFindFirst();
    return 0;
}


void testListItrFindFirst()
{
    void *te;
    ListItr begin;
    ListItr end;
	ListItr test;
	int num = 12;
	int num2 = 54;
	int num3 = 5;
    int num4 = 84;
	int num5 = 5;
	List *list;
	list = ListCreate();
	end = ListPushHead(list, &num);
	ListPushHead(list, &num2);
	ListPushHead(list, &num3);
    ListPushHead(list, &num4);
	begin = ListPushHead(list, &num5);
	test = ListItrFindFirst(begin, end, action, &num);
    te = ListItrGet(test);
    if(te == &num)
    {
        printf("find first test pass");
    }
    else 
    {
         printf("find first test fail");
    }

}

void testListItrForEach()
{
    void *te;
    ListItr begin;
    ListItr end;
	ListItr test;
	int num = 12;
	int num2 = 54;
	int num3 = 5;
    int num4 = 84;
	int num5 = 5;
	List *list;
	list = ListCreate();
	end = ListPushHead(list, &num);
	ListPushHead(list, &num2);
	ListPushHead(list, &num3);
    ListPushHead(list, &num4);
	begin = ListPushHead(list, &num5);
	test = ListItrForEach(begin, end, action, &num);
    te = ListItrGet(test);
    if(te == &num)
    {
        printf("for each test pass");
    }
    else 
    {
         printf("for each first test fail");
    }

}


void testListItrSort()
{
    void *te;
    ListItr begin;
    ListItr end;
	ListItr test;
	int num = 12;
	int num2 = 54;
	int num3 = 5;
    int num4 = 84;
	int num5 = 5;
	List *list;
	list = ListCreate();
	end = ListPushHead(list, &num);
	ListPushHead(list, &num2);
	ListPushHead(list, &num3);
    ListPushHead(list, &num4);
	begin = ListPushHead(list, &num5);
	test = ListItrSort(begin, end, action);
    te = ListItrGet(test);
    if(te == &num)
    {
        printf("for each test pass");
    }
    else 
    {
         printf("for each first test fail");
    }
}