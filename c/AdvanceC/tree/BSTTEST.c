#include <stdio.h>
#include <stdlib.h>
#include "BinTree.h"
#define PRINT_TEST(condition)\
{\
	if (condition)\
	{\
		printf("PASS (:\n");\
	}\
	else\
	{\
		printf("FAIL ):\n");\
	}\
}



/*================================ tests ==========================*/ 

void testBSTreeCreate();

void testBSTreeDestroy(); /* check for double free */

void testBSTreeInsert(); /* check insert first */

void testBSTreeInsert2(); 

void testBSTreeFindFirst();

void testBSTreeItrNext();

void testBSTreeItrPrev();

void testBSTreeItrGet();

void testBSTreeForEach();

void testBSTreeForEach2();

void testBSTreeForEach3();

/*=================================================================*/ 


int main()
{
    testBSTreeCreate();
    testBSTreeDestroy();
    testBSTreeInsert();
    testBSTreeInsert2(); 
    testBSTreeFindFirst();
    testBSTreeItrNext();
    testBSTreeItrPrev();
    testBSTreeItrGet();
    testBSTreeForEach();
    testBSTreeForEach2();
    testBSTreeForEach3();
    return 0;
}

static int IsLess(void *_a, void *_b)
{
    if(*(int *) _a > *(int *) _b)
    {
        return 0;
    }
    return 1;
}


void testBSTreeCreate()
{
    BSTree *tree;
    tree = BSTreeCreate(IsLess);
    PRINT_TEST(tree != NULL);
}


void testBSTreeDestroy()
{
    BSTree *tree;
    tree = BSTreeCreate(IsLess);
    BSTreeDestroy(tree, NULL);
    BSTreeDestroy(tree, NULL);
    PRINT_TEST(1);
}


void testBSTreeInsert()
{
    BSTreeItr itr;
    int num = 9;
    BSTree *tree;
    tree = BSTreeCreate(IsLess);
    itr = BSTreeInsert(tree, &num);
    PRINT_TEST (itr != NULL);
    BSTreeDestroy(tree, NULL);
}

void testBSTreeInsert2()
{
    BSTreeItr itr;
    int num1 = 9;
    int num2 = 19;
    int num3 = 1;
    int num4 = -9;
    int num5 = 18;
    BSTree *tree;
    tree = BSTreeCreate(IsLess);
    BSTreeInsert(tree, &num1);
    BSTreeInsert(tree, &num2);
    BSTreeInsert(tree, &num3);
    BSTreeInsert(tree, &num4);
    BSTreeInsert(tree, &num5);
    itr = BSTreeInsert(tree, &num4);
    PRINT_TEST (itr != NULL);
    BSTreeDestroy(tree, NULL);
}




int Check(void * _element, void* _context)
{
    if (_element == _context)
    {
        return 0;
    }
    return 1;
}


void testBSTreeFindFirst()
{
    BSTreeItr itr;
    int num1 = 9;
    int num2 = 19;
    int num3 = 1;
    int num4 = -9;
    int num5 = 18;
    BSTree *tree;
    tree = BSTreeCreate(IsLess);
    BSTreeInsert(tree, &num1);
    BSTreeInsert(tree, &num2);
    BSTreeInsert(tree, &num3);
    BSTreeInsert(tree, &num4);
    BSTreeInsert(tree, &num5);
    itr = BSTreeFindFirst(tree, Check, &num3);
    PRINT_TEST(itr != NULL);
    BSTreeDestroy(tree, NULL);
}








void testBSTreeItrNext()
{
    BSTreeItr test;
    BSTreeItr itr;
    int num1 = 9;
    int num2 = 19;
    int num3 = 1;
    int num4 = -9;
    int num5 = 18;
    BSTree *tree;
    tree = BSTreeCreate(IsLess);
    BSTreeInsert(tree, &num1);
    test = BSTreeInsert(tree, &num2);
    BSTreeInsert(tree, &num3);
    BSTreeInsert(tree, &num4);
    itr = BSTreeInsert(tree, &num5);
    itr = BSTreeItrNext(itr);
    PRINT_TEST(itr == test);
    BSTreeDestroy(tree, NULL);
}

void testBSTreeItrPrev()
{
    BSTreeItr test;
    BSTreeItr itr;
    int num1 = 9;
    int num2 = 19;
    int num3 = 1;
    int num4 = -9;
    int num5 = 18;
    BSTree *tree;
    tree = BSTreeCreate(IsLess);
    test = BSTreeInsert(tree, &num1);
    BSTreeInsert(tree, &num2);
    BSTreeInsert(tree, &num3);
    BSTreeInsert(tree, &num4);
    itr = BSTreeInsert(tree, &num5);
    itr = BSTreeItrPrev(itr);
    PRINT_TEST(itr == test);
    BSTreeDestroy(tree, NULL);
}

void testBSTreeItrGet()
{
    void *test;
    BSTreeItr itr;
    int num1 = 9;
    int num2 = 19;
    int num3 = 1;
    int num4 = -9;
    int num5 = 18;
    BSTree *tree;
    tree = BSTreeCreate(IsLess);
    BSTreeInsert(tree, &num1);
    BSTreeInsert(tree, &num2);
    BSTreeInsert(tree, &num3);
    BSTreeInsert(tree, &num4);
    itr = BSTreeInsert(tree, &num5);
    test = BSTreeItrGet(itr);
    PRINT_TEST(test == &num5);
    BSTreeDestroy(tree, NULL);
}

int PrintFor(void * _element, void* _context)
{
    printf("%d \n", *(int*)_element);
    return 1;
}


void testBSTreeForEach()
{
    int num1 = 50;
    int num2 = 40;
    int num3 = 60;
    int num4 = 30;
    int num5 = 45;
    int num6 = 55;
    int num7 = 70;
    BSTree *tree;
    tree = BSTreeCreate(IsLess);
    BSTreeInsert(tree, &num1);
    BSTreeInsert(tree, &num2);
    BSTreeInsert(tree, &num3);
    BSTreeInsert(tree, &num4);
    BSTreeInsert(tree, &num5);
    BSTreeInsert(tree, &num6);
    BSTreeInsert(tree, &num7);
    BSTreeForEach(tree, BSTREE_TRAVERSAL_PREORDER, PrintFor, &num2);
    printf("\n");
    BSTreeDestroy(tree, NULL);
}

void testBSTreeForEach2()
{
    int num1 = 9;
    int num2 = 19;
    int num3 = 1;
    int num4 = -9;
    int num5 = 18;
    BSTree *tree;
    tree = BSTreeCreate(IsLess);
    BSTreeInsert(tree, &num1);
    BSTreeInsert(tree, &num2);
    BSTreeInsert(tree, &num3);
    BSTreeInsert(tree, &num4);
    BSTreeInsert(tree, &num5);
    BSTreeForEach(tree, BSTREE_TRAVERSAL_INORDER, PrintFor, &num2);
    printf("\n");
    BSTreeDestroy(tree, NULL);
}

void testBSTreeForEach3()
{
    int num1 = 9;
    int num2 = 19;
    int num3 = 1;
    int num4 = -9;
    int num5 = 18;
    BSTree *tree;
    tree = BSTreeCreate(IsLess);
    BSTreeInsert(tree, &num1);
    BSTreeInsert(tree, &num2);
    BSTreeInsert(tree, &num3);
    BSTreeInsert(tree, &num4);
    BSTreeInsert(tree, &num5);
    BSTreeForEach(tree, BSTREE_TRAVERSAL_POSTORDER, PrintFor, &num2);
    printf("\n");
    BSTreeDestroy(tree, NULL);
}