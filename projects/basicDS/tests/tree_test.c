#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "tree_err.h"



void Treetest()
{
    Tree *tree;
    tree = TreeCreate();
    TreeInsert(tree, 80);
    TreeInsert(tree, 82);
    TreeInsert(tree, -2);
    TreeInsert(tree, -64);
    TreeInsert(tree, 34);
    TreeInsert(tree, -88);
    TreeInsert(tree, 5);
}

void TestTreeIsDataFound()
{
    int found;
    Tree *tree;
    tree = TreeCreate();
    TreeInsert(tree, 80);
    TreeInsert(tree, -82);
    found = TreeIsDataFound (tree, 80);
    if (found == 1)
    {
        printf("test Tree Is Data Found: pass\n");
    }
    else
    {
        printf("test Tree Is Data Found: fail\n");
    }
    found = TreeIsDataFound (tree, -82);
    if (found == 1)
    {
        printf("test Tree Is Data Found 2: pass\n");
    }
    else
    {
        printf("test Tree Is Data Found 2: fail\n");
    }
    found = TreeIsDataFound (tree, 4);
    if (found == 0)
    {
        printf("test Tree Is Data Found 3: pass\n");
    }
    else
    {
        printf("test Tree Is Data Found 3: fail\n");
    }
    found = TreeIsDataFound (tree, 8);
    if (found == 0)
    {
        printf("test Tree Is Data Found 4: pass\n");
    }
    else
    {
        printf("test Tree Is Data Found 4: fail\n");
    }
    TreeDestroy(tree);
}

void TestTreeDestroy()
{
    Tree *tree;
    tree = TreeCreate();
    TreeInsert(tree, 80);
    TreeInsert(tree, 82);
    TreeInsert(tree, -2);
    TreeInsert(tree, -64);
    TreeDestroy(tree);
    TreeDestroy(tree);
    printf("Test Tree Destroy: pass\n");
}

void testTreePrint()
{
    int isTrue;
    Tree *tree1;
    if (TreeInsert(tree1, 80) == ERR_NULL)
    {
        printf("not initil test 1: pass (:\n");
    }
    else
    {
        printf("not initil 1: fail \n");
    }
    tree1 = TreeCreate();
    TreeInsert(tree1, 80);
    TreeInsert(tree1, 82);
    if (TreeIsDataFound(tree1, 80) == 1)
    {
        printf("found test 1: pass (:\n");
    }
    else
    {
        printf("found test 1: fail \n");
    }
    TreeInsert(tree1, 3);
    TreeInsert(tree1, 64);
    TreeInsert(tree1, -7);
    TreeInsert(tree1, 57);
    TreeInsert(tree1, -18);
    if (TreeIsDataFound(tree1, -18) == 1)
    {
        printf("found test 2: pass (:\n");
    }
    else
    {
        printf("found test 2: fail \n");
    }
    if (TreeIsDataFound(tree1, 5) == 0)
    {
        printf("found test 3: pass (:\n");
    }
    else
    {
        printf("found test 3: fail \n");
    }
    TreeInsert(tree1, -89);
    TreeInsert(tree1, -89);
    if (TreeInsert(tree1, -89) == ERR_INPUT_ALREADY_EXIST)
    {
        printf("ERR_INPUT_ALREADY_EXIST test 1: pass (:\n");
    }
    else
    {
        printf("ERR_INPUT_ALREADY_EXIST test 1: fail \n");
    }
    TreePrint(tree1, 0);
    TreePrint(tree1, 1);
    TreePrint(tree1, 2);
}

void TestCheckIfFull()
{
    Tree *tree;
    tree = TreeCreate();
    TreeInsert(tree, 10);
    TreeInsert(tree, 5);
    if (CheckIfFull(tree) == 0)
    {
        printf("check if full pass\n");
    }
    else
    {
        printf("check if full fail\n");
    }
    TreeInsert(tree, 11);
    if (CheckIfFull(tree) == 1)
    {
        printf("check if full pass\n");
    }
    else
    {
        printf("check if full fail\n");
    }
}

void TestCheckIfFull2()
{
    Tree *tree;
    tree = TreeCreate();
    TreeInsert(tree, 5);
    TreeInsert(tree, 2);
    TreeInsert(tree, 1);
    if (CheckIfFull(tree) == 0)
    {
        printf("check if full 2  pass\n");
    }
    else
    {
        printf("check if full 2 fail\n");
    }
}
void testTreenull()
{
    Tree *tree1;
    tree1 = TreeCreate();
    if (TreeInsert(NULL, 80) == ERR_NULL)
    {
        printf("null test pass (:\n");
    }
    else
    {
        printf("null test fail ");
    }
}


void testIsSame()
{
    Tree *tree1;
    Tree *tree2;
    tree1 = TreeCreate();
    tree2 = TreeCreate();
    TreeInsert(tree1, 5);
    TreeInsert(tree1, 3);
    TreeInsert(tree1, 2);
    TreeInsert(tree2, 5);
    TreeInsert(tree2, 3);
    TreeInsert(tree2, 2);
    if (CheckIfSimilar(tree1, tree2) == 1)
    {
        printf("pass (:\n");
    }
    else
    {
        printf("fail ):\n");
    }
    

}

int main()
{
    /* Treetest();
    TestTreeIsDataFound(); 
    TestTreeDestroy();
    testTreePrint();
    testTreenull();  */
    /*TestCheckIfFull();*/
    TestCheckIfFull2();
    testIsSame();
}
