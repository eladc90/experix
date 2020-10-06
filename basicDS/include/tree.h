#ifndef __TREE_H__
#define __TREE_H__
#include "tree_err.h"

typedef struct Tree Tree;

typedef struct Node Node;

/*
this function create a tree

output:
    1.a pointer to the tree created.

error:
    NULL ERR if failed to create the struct
*/

Tree *TreeCreate();

/*
this function destroy the tree

input:
    a pointer to the tree root;
*/
void TreeDestroy(Tree *_tree);

/*insert a new node to the tree if the data is alrady stored in the tree do nothing
input:
    1. a point to the tree
    2. int to enter
output:
    1.status ERR_OK.
errors:
    1. NULL tree:           ERR_NOT_INITIALZED
    2. data exist:   ERR_INPUT_ALREADY_EXIST
*/

ADTErr TreeInsert(Tree *_tree, int _data);

/* this function get a tree and data and return if this 

data is in the tree

input:
    a pointer to a tree and data
output:
    return NOT_FOUND if the data is not in the tree and FOUND if does
error:
    ERR_NULL if the tree is NULL
*/

int TreeIsDataFound (Tree *_tree, int _data);

/* this function print the tree 

input:
    a pointer to a tree and printing methot 
    0 = PRE_ORDER
    1 = IN_ORDER
    2 = POST_ORDER
output:
    print the tree to the screen
*/

void TreePrint (Tree *_tree, TreeTraverse _traveseMode);

int CheckIfFull(Tree *_root);














#endif /*__TREE_H__ */
