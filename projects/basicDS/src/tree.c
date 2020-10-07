#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "tree_err.h"
#define TRUE 1
#define FALSE 0
#define MAGIC_NUMBER 487232456
#define RIGHT 0
#define LEFT 1
#define NOT_FOUND 0
#define FOUND 1






static void InOrderPrint(Node *_tree);

static void PostOrderPrint(Node *_tree);

static void PreOrderPrint(Node *_tree);

static Node *CreateNode ();

static int checkIfExist (Tree *_tree, int _data);

static void FreeTree(Node *_tree);

int CheckFull(Node *_root);



struct Node 
{
    int m_data;
    Node *m_left;
    Node *m_right;
    Node *m_father;
    int m_magicNumber;
};

struct Tree
{
    Node *m_root;
    int m_magicNumber;
};


/* statics function */

/* this function create a node */

static Node *CreateNode ()
{
    Node *new;
    new = (Node *) malloc (sizeof(Node));
    if (new == NULL)
    {
        return NULL;
    }
    new -> m_magicNumber = MAGIC_NUMBER;
    new -> m_left = NULL;
    new -> m_father = NULL;
    new -> m_right = NULL;
    return new;
    
}

/* this function destroy the nodes on the tree */

 
static void FreeTree(Node *_tree)
{
    if (_tree == NULL)
    {
        return;
    }
    FreeTree(_tree -> m_left);
    FreeTree(_tree -> m_right);
    free (_tree);   
}

/* function of print method */

static void PreOrderPrint(Node *_tree)
{
    if (_tree == NULL)
    {
        return;
    }
    printf("%d,", _tree -> m_data);
    PreOrderPrint (_tree -> m_left);
    PreOrderPrint (_tree -> m_right);
}

static void InOrderPrint(Node *_tree)
{
    if (_tree == NULL)
    {
        return;
    }
    InOrderPrint (_tree -> m_left);
    printf("%d,", _tree -> m_data);
    InOrderPrint (_tree -> m_right);
}

static void PostOrderPrint(Node *_tree)
{
    if (_tree == NULL)
    {
        return;
    }
    InOrderPrint (_tree -> m_left);
    InOrderPrint (_tree -> m_right);
    printf("%d,", _tree -> m_data);
}

/* this function check if data exist in the tree */

static int checkIfExist (Tree *_tree, int _data)
{
    int isLeft;
    Node *currentNode;
    Node *tempFather;
    if (_tree == NULL)
    {
        return ERR_NULL;
    }
    tempFather = _tree -> m_root;
    currentNode = _tree -> m_root;
    while (currentNode != NULL)
    {
        tempFather = currentNode;

        if (_data > tempFather -> m_data)
        {
            currentNode = currentNode -> m_right;
            isLeft = RIGHT;
        }
        else if (_data < tempFather -> m_data)
        {
            currentNode = currentNode -> m_left;
            isLeft = LEFT;
        }
        else
        {
            return FOUND;
        }
    }
    return NOT_FOUND;
}



/* this function create a tree and a root node */

Tree *TreeCreate()
{
    Tree *tree; 
    tree = (Tree *) malloc (sizeof(Tree));
    if (tree == NULL)
    {
        return NULL;
    }
    tree -> m_magicNumber = MAGIC_NUMBER;
    tree -> m_root = NULL;
    return tree;
}



void TreeDestroy(Tree *_tree)
{
    if (_tree == NULL)
    {
        return;
    }
    if (_tree -> m_magicNumber == MAGIC_NUMBER)
    {
        FreeTree(_tree -> m_root);
        _tree -> m_magicNumber = 0;
        free(_tree);
    }
}





/* this function check the location to insert a new node on the tree and create the node */

ADTErr TreeInsert(Tree *_tree, int _data)
{
    int LeftOrRight;
    Node *currentNode;
    Node *tempFather;
    if (_tree == NULL || _tree -> m_magicNumber != MAGIC_NUMBER)
    {
        return ERR_NULL;
    }
    if (_tree -> m_root == NULL)
    {
        currentNode = CreateNode();
        currentNode -> m_data = _data;
        _tree -> m_root = currentNode;
        return ERR_OK;
    }
    tempFather = _tree -> m_root;
    currentNode = _tree -> m_root;

/* check where to enter the tree */

    while (currentNode != NULL)
    {
        tempFather = currentNode;

        if (_data > tempFather -> m_data)
        {
            currentNode = currentNode -> m_right;
            LeftOrRight = RIGHT;
        }
        else if  (_data < tempFather -> m_data)
        {
            currentNode = currentNode -> m_left;
            LeftOrRight = LEFT;
        }
        else
        {
            return ERR_INPUT_ALREADY_EXIST;
        }
    }

/* create new node and initial the data */

    currentNode = CreateNode();
    currentNode -> m_data = _data;
    currentNode -> m_magicNumber = MAGIC_NUMBER;
    if (currentNode == NULL)
    {
        return ERR_NULL;
    }
    currentNode -> m_father = tempFather;
    if (LeftOrRight == LEFT)
    {
        currentNode -> m_father -> m_left = currentNode;
    }
    else
    {
        currentNode -> m_father -> m_right = currentNode;
    }
    return ERR_OK;
}

/* this function check if data exist in the tree */

int TreeIsDataFound (Tree *_tree, int _data)
{
    int CheckData;
    if (_tree == NULL)
    {
        return ERR_NULL;
    }
    CheckData = checkIfExist(_tree, _data);
    if (CheckData == NOT_FOUND)
    {
        return NOT_FOUND;
    }
    else
    {
        return FOUND;
    }
}


void TreePrint (Tree *_tree, TreeTraverse _traveseMode)
{
    if (_tree == NULL || _traveseMode < 0 || _traveseMode > 2|| _tree->m_magicNumber != MAGIC_NUMBER)
    {
        return;
    }
    if (_traveseMode == PRE_ORDER)
    {
        PreOrderPrint(_tree -> m_root);
        printf("\n");
        return;
    }
    if (_traveseMode == IN_ORDER)
    {
        InOrderPrint(_tree -> m_root);
        printf("\n");
        return;
    }
    if (_traveseMode == POST_ORDER)
    {
        PostOrderPrint(_tree -> m_root);
        printf("\n");
        return;
    }
    return;
}

int CheckIfFull(Tree *_root)
{
    if (_root == NULL)
    {
        return 0;
    }
    CheckFull (_root -> m_root);
}


int CheckFull(Node *_root)
{
    if (_root -> m_left == NULL && _root -> m_right == NULL)
    {
        return TRUE;
    }
    else if (_root -> m_left == NULL || _root -> m_right == NULL)
    {
        return FALSE;
    }
    return CheckFull(_root -> m_left) && CheckFull(_root -> m_right);
}



int CheckIfSimilar(Tree *_firstRoot, Tree *_secRoot)
{
    if (_firstRoot == NULL || _secRoot == NULL)
    {
        return FALSE;
    }
    IsSimilar(_firstRoot -> m_root, _secRoot -> m_root);
}


int IsSimilar(Node *_first, Node *_second)
{
    if (_first == NULL && _second == NULL)
    {
        return TRUE;
    }
    if (_first == NULL ||  _second == NULL)
    {
        return FALSE;
    }
    return (IsSimilar(_first -> m_left, _second -> m_left) && IsSimilar(_first -> m_right, _second -> m_right));
}




