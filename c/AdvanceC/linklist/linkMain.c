#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "iter.h"
#include "listfunctions.h"

void elementDestroy(void* _item);




void testListCreate(); /* check list create */

void testListDestroy(); /* check for doble free */
void testListDestroy2();
void testListDestroy3();
void testListDestroy4(); /* check for send null */ 

void testListPushHead(); /* check push null */
void testListPushHead2(); /* check item NULL */
void testListPushHead3(); /* check if push correctly */

void testListPushTail();
void testListPushTail2();
void testListPushTail3();

void testListPopTail(); 
void testListPopTail2(); /* check for under Flow */
void testListPopTail3(); /* check for list = null */
void testListPopTail4(); /* check for item = null */

void testListPophead();
void testListPophead2(); /* check for under Flow */
void testListPophead3(); /* check for list = null */
void testListPophead4(); /* check for item = null */

/*================= iterator test =======================*/ 

void testListItrBegin();
void testListItrBegin2();
void testListItrBegin3();

void testListItrEnd();
void testListItrEnd2();

void testListItrEquals();
void testListItrEquals2();
void testListItrEquals3();

void testListItrNext();

void testListItrPrev();

void testListItrGet();

void testListItrSet();
void testListItrSet2();

void testListItrInsertBefore();

void testListItrRemove();


/*================= list functions test =======================*/ 

void testListItrFindFirst();

void testListItrForEach();

void testListItrSort();

void testListItrSplice();

void testListItrCut();




void testListSize();

int main()
{
	testListCreate();
	testListDestroy();
	testListDestroy2();
 	testListDestroy3();
	testListDestroy4();

	testListPushHead();
	testListPushHead2();
	testListPushHead3();

	testListPushTail();
	testListPushTail2();
	testListPushTail3();

	testListPopTail();
	testListPopTail2(); 
	testListPopTail3();
	testListPopTail4();

	testListPophead();
	testListPophead2();
	testListPophead3();
	testListPophead4();

	testListSize();
	testListItrBegin();
	testListItrBegin2();
	testListItrBegin3();

	testListItrEnd();
	testListItrEnd2();

	testListItrEquals();
	testListItrEquals2();
	testListItrEquals3();

	testListItrNext();

	testListItrPrev();

	testListItrGet();

	testListItrSet();
	testListItrSet2();

	testListItrInsertBefore();

	testListItrRemove();  
	testListItrFindFirst();
	testListItrForEach();
	testListItrSort(); 
	testListItrSplice();
	testListItrCut();
	return 0;
}

void testListItrBegin()
{
	void *te;
	ListItr test;
	int num = 12;
	int num2 = 54;
	int num3 = 5;
	List *list;
	list = ListCreate();
	ListPushHead(list, &num);
	ListPushHead(list, &num2);
	ListPushHead(list, &num3);
	test = ListItrBegin(list);
	te = ListItrGet(test);
	if (te == &num3)
	{
		printf("List Itr Begin test 1: pass \n");
	}
	else
	{
		printf("List Itr Begin test 1: fail \n");
	}
}


void testListItrBegin2()
{
	ListItr test;
	List *list;
	list = ListCreate();
	test = ListItrBegin(list);
	if (ListItrNext(test) == test)
	{
		printf("List Itr Begin test 2: pass \n");
	}
	else
	{
		printf("List Itr Begin test 2: fail \n");
	}
}

void testListItrBegin3()
{
	ListItr te;
	ListItr test;
	List *list;
	list = ListCreate();
	test = ListItrBegin(list);
	te = ListItrPrev(test);
	if (ListItrPrev(te) == te)
	{
		printf("List Itr Begin test 2: pass \n");
	}
	else
	{
		printf("List Itr Begin test 2: fail \n");
	}
}

void testListItrEnd()
{
	void *te;
	ListItr test;
	int num = 12;
	int num2 = 54;
	int num3 = 5;
	List *list;
	list = ListCreate();
	ListPushHead(list, &num);
	ListPushHead(list, &num2);
	ListPushHead(list, &num3);
	test = ListItrEnd(list);
	te = ListItrNext(test);
	if (te == test)
	{
		printf("List Itr end test 1: pass \n");
	}
	else
	{
		printf("List Itr end test 1: fail \n");
	}
}



void testListItrEnd2()
{
	ListItr test;
	List *list;
	list = ListCreate();
	test = ListItrEnd(list);
	if (ListItrNext(test) == test)
	{
		printf("List Itr end test 2: pass \n");
	}
	else
	{
		printf("List Itr end test 2: fail \n");
	}
}


void testListItrEquals()
{
	void *te;
	ListItr test;
	int num = 12;
	int num2 = 54;
	int num3 = 5;
	List *list;
	list = ListCreate();
	ListPushHead(list, &num);
	ListPushHead(list, &num2);
	ListPushHead(list, &num3);
	test = ListItrEnd(list);
	te = ListItrNext(test);
	if (ListItrEquals(test, te) == 1)
	{
		printf("List Itr Equals test 1: pass \n");
	}
	else
	{
		printf("List Itr Equals test 1: fail \n");
	}
}

void testListItrEquals2()
{
	void *te;
	ListItr test;
	int num = 12;
	int num2 = 54;
	int num3 = 5;
	List *list;
	list = ListCreate();
	ListPushHead(list, &num);
	ListPushHead(list, &num2);
	ListPushHead(list, &num3);
	test = ListItrEnd(list);
	te = ListItrPrev(test);
	te = ListItrPrev(te);
	if (ListItrEquals(test, te) == 0)
	{
		printf("List Itr Equals test 2: pass \n");
	}
	else
	{
		printf("List Itr Equals test 2: fail \n");
	}
}

void testListItrEquals3()
{
	void *te;
	ListItr test;
	int num = 12;
	int num2 = 54;
	int num3 = 5;
	List *list;
	list = ListCreate();
	ListPushHead(list, &num);
	ListPushHead(list, &num2);
	ListPushHead(list, &num3);
	test = ListItrEnd(list);
	te = ListItrPrev(test);
	te = ListItrPrev(te);
	if (ListItrEquals(NULL, te) == 0)
	{
		printf("List Itr Equals test 2: pass \n");
	}
	else
	{
		printf("List Itr Equals test 2: fail \n");
	}
}


void testListItrNext()
{
	void *te;
	ListItr test;
	int num = 12;
	int num2 = 54;
	int num3 = 5;
	List *list;
	list = ListCreate();
	ListPushHead(list, &num);
	ListPushHead(list, &num2);
	ListPushHead(list, &num3);
	test  = ListItrBegin(list);
	test = ListItrNext(test);
	te = ListItrGet(test);
	if (te == &num2)
	{
		printf("List Itr Next test 1: pass \n");
	}
	else
	{
		printf("List Itr Next test 1: fail \n");
	}
}



void testListItrPrev()
{
	void *te;
	ListItr test;
	int num = 12;
	int num2 = 54;
	int num3 = 5;
	List *list;
	list = ListCreate();
	ListPushHead(list, &num);
	ListPushHead(list, &num2);
	ListPushHead(list, &num3);
	test  = ListItrEnd(list);
	test = ListItrPrev(test);
	te = ListItrGet(test);
	if (te == &num)
	{
		printf("List Itr prev test 1: pass \n");
	}
	else
	{
		printf("List Itr prev test 1: fail \n");
	}
}


void testListItrGet()
{
	void *te;
	ListItr test;
	int num = 12;
	int num2 = 54;
	int num3 = 5;
	List *list;
	list = ListCreate();
	ListPushHead(list, &num);
	ListPushHead(list, &num2);
	ListPushHead(list, &num3);
	test  = ListItrEnd(list);
	test = ListItrPrev(test);
	te = ListItrGet(test);
	if (te == &num)
	{
		printf("List Itr get test 1: pass \n");
	}
	else
	{
		printf("List Itr get test 1: fail \n");
	}
}


void testListItrSet()
{
	void *te;
	ListItr test;
	int num = 12;
	int num2 = 54;
	int num3 = 5;
	List *list;
	list = ListCreate();
	ListPushHead(list, &num);
	ListPushHead(list, &num2);
	test = ListItrBegin(list);
	ListItrSet(test, &num3);
	te = ListItrGet(test);
	if (te == &num3)
	{
		printf("List Itr Set test 1: pass \n");
	}
	else
	{
		printf("List Itr Set test 1: fail \n");
	}
}

void testListItrSet2()
{
	void *te;
	ListItr test;
	int num3 = 5;
	List *list;
	list = ListCreate();
	test = ListItrEnd(list);
	te = ListItrSet(test, &num3);
	if (te == NULL)
	{
		printf("List Itr Set test 2: pass \n");
	}
	else
	{
		printf("List Itr Set test 2: fail \n");
	}
}


void testListItrInsertBefore()
{
	ListItr test;
	List *list;
	int num = 5;
	list = ListCreate();
	test = ListItrBegin(list);
	test = ListItrPrev(test);
	test = ListItrInsertBefore(test, &num);
	if (test == ListItrBegin(list))
	{
		printf("List Itr Insert Before test 1: pass \n");
	}
	else
	{
		printf("List Itr Insert Before 1: fail \n");
	}
}


void testListItrRemove()
{
	ListItr test;
	List *list;
	int num = 5;
	int num2 = 7;
	list = ListCreate();
	test = ListItrEnd(list);
	ListItrInsertBefore(test, &num);
	ListItrInsertBefore(test, &num2);
	test = ListItrEnd(list);
	test = ListItrPrev(test);
	ListItrRemove(test);
	test = ListItrEnd(list);
	test = ListItrPrev(test);
	ListItrRemove(test);
	test = ListItrEnd(list);
	if (test == ListItrNext(test))
	{
		printf("Remove test 1: pass \n");
	}
	else
	{
		printf("Remove1: fail \n");
	}
}









void testprev()
{
	void *te;
	ListItr test;
	int num = 12;
	int num2 = 54;
	int num3 = 5;
	List *list;
	list = ListCreate();
	ListPushHead(list, &num);
	ListPushHead(list, &num2);
	ListPushHead(list, &num3);
	test = ListItrEnd(list);
	te = ListItrNext(test);
	if (te == test)
	{
		printf("List Itr end test 1: pass \n");
	}
	else
	{
		printf("List Itr end test 1: fail \n");
	}
}



void testListCreate()
{
	List *list;
	list = ListCreate();
	if (list != NULL)
	{
		printf("list create test 1: pass \n");
	}
	else
	{
		printf("list create test 1: fail \n");
	}
	ListDestroy(&list, NULL);
}


void testListDestroy()
{
	List *list;
	list = ListCreate();
	ListDestroy(&list, NULL);
	ListDestroy(&list, NULL);
	printf("list Destroy test 1: pass \n");
}




void testListDestroy2()
{
	List *list;
	list = ListCreate();
	ListDestroy(&list, NULL);
	printf("list Destroy test 2: pass \n");
}


void elementDestroy(void* _item)
{
	if (_item != NULL)
	{
		free( _item);
	}
	return;
}

void testListDestroy3()
{
	int index = 0;
	List *list;
	int **arr;
	list = ListCreate();
	if (arr != NULL)
	{
		for (; index < 5; index++)
		{
			arr = (int **) malloc (sizeof(int ) * 5);
			ListPushHead(list, &arr);
		}
	}
	ListDestroy(&list, elementDestroy);
	if (list == NULL)
	{
		printf("list Destroy test 3: pass \n");
	}
	else
	{
		printf("list Destroy test 3: fail \n");
	}	
}

void testListDestroy4()
{
	List *list;
	list = NULL;
	ListDestroy(&list, NULL);
	printf("list Destroy test 4: pass \n");
}

void testListPushHead()
{
	int status;
	List *list;
	list = ListCreate();
	status = ListPushHead(NULL, NULL);
	if (status == LIST_ERR_NULL)
	{
		printf("list push test 1: pass \n");
	}
	else
	{
		printf("list push test 1: fail \n");
	}
	ListDestroy(&list, NULL);
}

void testListPushHead2()
{
	int status;
	List *list;
	list = ListCreate();
	status = ListPushHead(list, NULL);
	if (status == LIST_NULL_ELEMENT_ERROR)
	{
		printf("list push test 2: pass \n");
	}
	else
	{
		printf("list push test 2: fail \n");
	}
	ListDestroy(&list, NULL);
} 

void testListPushHead3()
{
	void* status;
	int num = 12;
	int num2 = 54;
	int num3 = 5;
	List *list;
	list = ListCreate();
	ListPushHead(list, &num);
	ListPushHead(list, &num2);
	ListPushHead(list, &num3);
	ListPopHead(list, &status);
	if (status == &num3)
	{
		printf("list push test 3: pass \n");
	}
	else
	{
		printf("list push test 3: fail \n");
	}
	ListPopHead(list, &status);
	if (status == &num2)
	{
		printf("list push test 4: pass \n");
	}
	else
	{
		printf("list push test 4: fail \n");
	}
	ListDestroy(&list, NULL);
} 












void testListPushTail()
{
	int status;
	List *list;
	list = ListCreate();
	status = ListPushTail(NULL, NULL);
	if (status == LIST_ERR_NULL)
	{
		printf("list push tail test 1: pass \n");
	}
	else
	{
		printf("list push tail test 1: fail \n");
	}
	ListDestroy(&list, NULL);
}

void testListPushTail2()
{
	int status;
	List *list;
	list = ListCreate();
	status = ListPushTail(list, NULL);
	if (status == LIST_NULL_ELEMENT_ERROR)
	{
		printf("list push tail test 2: pass \n");
	}
	else
	{
		printf("list push tail test 2: fail \n");
	}
	ListDestroy(&list, NULL);
} 

void testListPushTail3()
{
	void* status;
	int num = 12;
	int num2 = 54;
	int num3 = 5;
	List *list;
	list = ListCreate();
	ListPushTail(list, &num);
	ListPushTail(list, &num2);
	ListPushTail(list, &num3);
	ListPopTail(list, &status);
	if (status == &num3)
	{
		printf("list push tail test 3: pass \n");
	}
	else
	{
		printf("list push tail test 3: fail \n");
	}
	ListPopTail(list, &status);
	if (status == &num2)
	{
		printf("list push tail test 4: pass \n");
	}
	else
	{
		printf("list push tail  test 4: fail \n");
	}
	ListDestroy(&list, NULL);
} 


void testListPopTail()
{
	List *list;
	void* status;
	int num = 12;
	int num2 = 54;
	int num3 = 5;
	list = ListCreate();
	ListPushTail(list, &num);
	ListPushTail(list, &num2);
	ListPushTail(list, &num3);
	ListPopTail(list, &status);
	if (status == &num3)
	{
		printf("list pop tail test 1: pass \n");
	}
	else
	{
		printf("list pop tail test 1: fail \n");
	}
	ListDestroy(&list, NULL);
}

void testListPopTail2()
{
	List *list;
	void *test;
	int status;
	list = ListCreate();
	status = ListPopTail(list, &test);
	if (status == LIST_ERR_UNDERFLOW)
	{
		printf("list pop tail test 2: pass \n");
	}
	else
	{
		printf("list pop tail test 2: fail \n");
	}
	ListDestroy(&list, NULL);
}

void testListPopTail3()
{
	List *list;
	void *test;
	int status;
	list = NULL;
	status = ListPopTail(list, &test);
	if (status == LIST_ERR_NULL)
	{
		printf("list pop tail test 3: pass \n");
	}
	else
	{
		printf("list pop tail test 3: fail \n");
	}
	ListDestroy(&list, NULL);
}

void testListPopTail4()
{
	List *list;
	int status;
	list = ListCreate();
	status = ListPopTail(list, NULL);
	if (status == LIST_ERR_NULL)
	{
		printf("list pop tail test 4: pass \n");
	}
	else
	{
		printf("list pop tail test 4: fail \n");
	}
	ListDestroy(&list, NULL);
}






void testListPophead()
{
	List *list;
	void* status;
	int num = 82;
	int num2 = 524;
	int num3 = 3;
	list = ListCreate();
	ListPushTail(list, &num);
	ListPushTail(list, &num2);
	ListPushTail(list, &num3);
	ListPopHead(list, &status);
	if (status == &num)
	{
		printf("list pop head test 1: pass \n");
	}
	else
	{
		printf("list pop head test 1: fail \n");
	}
	ListDestroy(&list, NULL);
}

void testListPophead2()
{
	List *list;
	void *test;
	int status;
	list = ListCreate();
	status = ListPopHead(list, &test);
	if (status == LIST_ERR_UNDERFLOW)
	{
		printf("list pop head test 2: pass \n");
	}
	else
	{
		printf("list pop head test 2: fail \n");
	}
	ListDestroy(&list, NULL);
}

void testListPophead3()
{
	List *list;
	void *test;
	int status;
	list = NULL;
	status = ListPopHead(list, &test);
	if (status == LIST_ERR_NULL)
	{
		printf("list pop head test 3: pass \n");
	}
	else
	{
		printf("list pop head test 3: fail \n");
	}
	ListDestroy(&list, NULL);
}

void testListPophead4()
{
	List *list;
	int status;
	list = ListCreate();
	status = ListPopHead(list, NULL);
	if (status == LIST_ERR_NULL)
	{
		printf("list pop head test 4: pass \n");
	}
	else
	{
		printf("list pop head test 4: fail \n");
	}
	ListDestroy(&list, NULL);
}

void testListSize()
{
	size_t test;
	List *list;
	int num = 82;
	int num2 = 524;
	int num3 = 3;
	list = ListCreate();
	ListPushTail(list, &num);
	ListPushTail(list, &num2);
	ListPushTail(list, &num3);
	test = ListSize(list);
	if (test == 3)
	{
		printf("List Size test 1: pass \n");
	}
	else
	{
		printf("List Size test 1: fail \n");
	}
	ListDestroy(&list, NULL);
}











int action(void* _num, void* _item)
{

	if (_num == _item)
	{
		return 0;
	}
	return 1;
}

int actionPrint(void* _num, void* _item)
{
	
	int *i = _num;
	printf("%d\n", *i);
	return 1;
}

int sortFun(void* _num, void* _num2)
{
	int *i = _num;
	int *j = _num2;
	if (*i > *j)
	{
		return 1;
	}
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
	ListPushHead(list, &num);
	ListPushHead(list, &num2);
	ListPushHead(list, &num3);
    ListPushHead(list, &num4);
	ListPushHead(list, &num5);
	begin = ListItrBegin(list);
	end = ListItrEnd(list);
	test = ListItrFindFirst(begin, end, action, &num);
    te = ListItrGet(test);
    if(te == &num)
    {
        printf("find first test pass\n");
    }
    else 
    {
         printf("find first test fail\n");
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
	ListPushHead(list, &num);
	ListPushHead(list, &num2);
	ListPushHead(list, &num3);
    ListPushHead(list, &num4);
	ListPushHead(list, &num5);
	begin = ListItrBegin(list);
	end = ListItrEnd(list);
	test = ListItrForEach(begin, end, action, &num);
    te = ListItrGet(test);
    if(te == &num)
    {
        printf("for each test pass\n");
    }
    else 
    {
         printf("for each first test fail\n");
    }

}


void testListItrSort()
{

    ListItr begin;
    ListItr end;

	int num = 12;
	int num2 = 54;
	int num3 = 5;
    int num4 = 84;
	int num5 = 5;
	List *list;
	list = ListCreate();
	ListPushHead(list, &num);
	ListPushHead(list, &num2);
	ListPushHead(list, &num3);
    ListPushHead(list, &num4);
	ListPushHead(list, &num5);
	begin = ListItrBegin(list);
	end = ListItrEnd(list);
	ListItrSort(begin, end, sortFun);
	ListItrForEach(begin, end, actionPrint, &num);
    
}

void testListItrSplice()
{
	ListItr dest;
	ListItr begin;
    ListItr end;
	int num = 12;
	int num2 = 54;
	int num3 = 5;
    int num4 = 84;
	int num5 = 77;
	List *list;
	list = ListCreate();
	ListPushHead(list, &num);
	ListPushHead(list, &num2);
	ListPushHead(list, &num3);
    ListPushHead(list, &num4);
	ListPushHead(list, &num5);
	dest = ListItrBegin(list);
	begin = ListItrNext(dest);
	end = ListItrEnd(list);
	ListItrSplice(dest, begin, end);
	begin = ListItrBegin(list);
	ListItrForEach(begin, end, actionPrint, &num);
}



void testListItrCut()
{
	ListItr dest;
	ListItr begin;
    ListItr end;
	int num = 12;
	int num2 = 54;
	int num3 = 5;
    int num4 = 84;
	int num5 = 77;
	List *list;
	list = ListCreate();
	ListPushHead(list, &num);
	ListPushHead(list, &num2);
	ListPushHead(list, &num3);
    ListPushHead(list, &num4);
	ListPushHead(list, &num5);
	dest = ListItrBegin(list);
	begin = ListItrNext(dest);
	begin = ListItrNext(begin);
	end = ListItrEnd(list);
	ListItrCut(begin, end);
	begin = ListItrBegin(list);
	end = ListItrEnd(list);
	ListItrForEach(begin, end, actionPrint, &num);
}

















