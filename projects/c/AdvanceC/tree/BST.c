#include <stdio.h>
#include <stdlib.h>
#include "BinTree.h"

#define MAGIC_NUMBER 0XBEEFCAFE
#define UN_MAGIC_NUMBER 0XCAFEBABE





typedef struct Node Node;

struct Node 
{
    void *m_data;
    Node *m_left;
    Node *m_right;
    Node *m_father;
    Node *m_next;
    Node *m_prev;
};

struct BSTree
{
    Node m_sentinel;
    LessComparator m_method;
    size_t m_magicNumber;
};


struct BSTreeItr
{
    Node *m_itr;
};


/* ============================ global wrong node ==================================*/

static Node g_wrongNode = {NULL, &g_wrongNode, &g_wrongNode, &g_wrongNode};

BSTreeItr g_wrongIter = (BSTreeItr) (&g_wrongNode);

/*==================================================================================*/


/*=================================== static functions =============================*/

static void FreeTree(Node *_root, void (*_destroyer)(void*));

static Node* HandleIfFirst(Node *_root, void *_data);

static Node* CreateNode(void *_data);

static Node *PlaceToInsert(Node *_root ,void* _data, LessComparator _lessFunc, Node **_prev, Node **_next);

static Node* PutNode(Node *_father, LessComparator _lessFunc, void *_data);

static Node* FindInOrder(Node* _root, PredicateFunction _predicate, void* _context);

static BSTreeItr ForEachInOrder(Node *_root, ActionFunction _action, void* _context);

static BSTreeItr ForEachPostOrder(Node *_root, ActionFunction _action, void* _context);

static BSTreeItr ForEachPreOrder(Node *_root, ActionFunction _action, void* _context);

static int CheckIfLeaf(BSTreeItr _itr); 

static BSTreeItr RemoveFromTree(BSTreeItr _itr);

/*==================================================================================*/







/*================================== main functions =================================*/

BSTree* BSTreeCreate(LessComparator _less)
{
    BSTree *newTree;
    if (_less == NULL)
    {
        return NULL;
    }
    newTree = (BSTree *) malloc (sizeof (BSTree));
    if (newTree == NULL)
    {
        return NULL;
    }
    newTree -> m_magicNumber = MAGIC_NUMBER;
    newTree -> m_method = _less;
    newTree -> m_sentinel.m_right = NULL;
    newTree -> m_sentinel.m_left = NULL;
    newTree -> m_sentinel.m_father = &(newTree -> m_sentinel);
    return newTree;
}



void  BSTreeDestroy(BSTree* _tree, void (*_destroyer)(void*))
{
    if (_tree == NULL)
    {
        return;
    }
    if (_tree -> m_magicNumber == MAGIC_NUMBER)
    {
        FreeTree(_tree -> m_sentinel.m_left, _destroyer);
        _tree -> m_magicNumber = UN_MAGIC_NUMBER;
    }
    free(_tree);
}



BSTreeItr BSTreeInsert(BSTree* _tree, void* _item)
{
    Node *insertNode;
    Node *prev;
    Node *next;
    if (_tree == NULL || _tree -> m_magicNumber != MAGIC_NUMBER || _item == NULL)
    {
        return g_wrongIter; 
    }
    insertNode = HandleIfFirst(&(_tree -> m_sentinel), _item);
    if (insertNode != NULL)
    {
        return (BSTreeItr) insertNode;
    }
    insertNode = PlaceToInsert(_tree -> m_sentinel.m_left, _item, _tree -> m_method, &prev, &next);
    if (insertNode == NULL)
    {
        return (BSTreeItr) &(_tree -> m_sentinel);
    }
    insertNode = PutNode(insertNode, _tree -> m_method, _item);
    if (insertNode == NULL)
    {
        return (BSTreeItr) &(_tree -> m_sentinel);
    }
    insertNode -> m_prev = prev;
    insertNode -> m_next = next;
    if (next == NULL)
    {
        insertNode -> m_next = &(_tree -> m_sentinel);
    }
    if (prev == NULL)
    {
        insertNode -> m_next = insertNode;
    }
    return (BSTreeItr) insertNode;
}

BSTreeItr BSTreeFindFirst(const BSTree* _tree, PredicateFunction _predicate, void* _context)
{
    Node *node;
    if (_tree == NULL || _predicate == NULL || _context == NULL || _tree -> m_magicNumber != MAGIC_NUMBER)
    {
        return g_wrongIter;
    }
    node = FindInOrder(_tree -> m_sentinel.m_left, _predicate, _context);
    if (node == NULL)
    {
        return g_wrongIter; 
    }
    return (BSTreeItr) node;
}


BSTreeItr BSTreeItrBegin(const BSTree* _tree)
{
    Node *ptr = NULL;
    if(_tree == NULL || _tree->m_magicNumber != MAGIC_NUMBER)
    {
        return g_wrongIter;
    }
    if(_tree->m_sentinel.m_left == NULL)
    {
        return (BSTreeItr)&(_tree->m_sentinel);
    }

    ptr = _tree->m_sentinel.m_left;
    while (ptr ->m_left != NULL)
    {
        ptr = ptr->m_left;
    }
    return (BSTreeItr)ptr;
}

int BSTreeItrEquals(BSTreeItr _a, BSTreeItr _b)
{
    if(&_a == &_b)
    {
        return 1;
    }
    return 0;
}

BSTreeItr BSTreeItrNext(BSTreeItr _it)
{
    Node *node;
    if (_it == g_wrongIter)
    {
        return g_wrongIter;
    }
    node = ((Node*) _it)->m_next;
    if (node == NULL)
    {
        return g_wrongIter;
    }
    return (BSTreeItr) node;
}

BSTreeItr BSTreeItrPrev(BSTreeItr _it)
{
    Node *node;
    if (_it == g_wrongIter)
    {
        return g_wrongIter;
    }
    node = ((Node*) _it)->m_prev;
    if (node == (Node*)_it)
    {
        return g_wrongIter;
    }
    return (BSTreeItr) node;
}


 
BSTreeItr BSTreeItrEnd(const BSTree* _tree)
{
    Node *largest = NULL;
    if(_tree == NULL)
    {
        return g_wrongIter;
    }
    if(_tree->m_sentinel.m_left == NULL)
    {
        return (BSTreeItr)&(_tree->m_sentinel);
    }
    largest = _tree->m_sentinel.m_left;
    while (largest -> m_right != NULL)
    {
        largest = largest->m_right;
    }
    return (BSTreeItr)largest;
}



void* BSTreeItrGet(BSTreeItr _it)
{
    if (_it == g_wrongIter)
    {
        return g_wrongIter;
    }
    return ((Node*) _it) -> m_data;
}




BSTreeItr BSTreeForEach(const BSTree* _tree, TreeTraversalMode _mode, ActionFunction _action, void* _context)
{
    BSTreeItr itr = NULL;
    Node* root; 
    if (_tree == NULL || _action == NULL || _context == NULL || _mode > 2 || _mode < 0 || _tree -> m_magicNumber != MAGIC_NUMBER || _tree -> m_sentinel.m_left == NULL)
    {
        return g_wrongIter;
    }
    root = _tree -> m_sentinel.m_left;
    if (_mode == BSTREE_TRAVERSAL_INORDER)
    {
        itr = ForEachInOrder(root, _action, _context);
        return itr;
    }
    if (_mode == BSTREE_TRAVERSAL_POSTORDER)
    {
        ForEachPostOrder(root, _action, _context);
    }
    if (_mode == BSTREE_TRAVERSAL_PREORDER)
    {
        ForEachPreOrder(root, _action, _context);
    }
    return itr;
}


void* BSTreeItrRemove(BSTreeItr _it)
{
    void* item;
    BSTreeItr itr;
    if (_it == g_wrongIter)
    {
        return g_wrongIter;
    }
    itr = RemoveFromTree(_it);
    item = ((Node *)itr);
    return item;
}



/*==================================== aux functions ===================================*/



static BSTreeItr RemoveFromTree(BSTreeItr _itr)
{
    BSTreeItr temp;
    if (CheckIfLeaf(_itr))
    {
        return _itr;
    }
    ((Node *)_itr) ->  m_data = ((Node *)_itr) -> m_prev -> m_data;
    temp = RemoveFromTree(BSTreeItrPrev(_itr));
    return temp;
}






static Node* FindInOrder(Node* _root, PredicateFunction _predicate, void* _context)
{
    Node *node;
    if (_root == NULL)
    {
        return NULL;
    }
    if (_predicate(_root -> m_data, _context) == 0)
    {
        return _root;
    }
    node = FindInOrder(_root -> m_left, _predicate, _context);
    if (node != NULL)
    {
        return node;
    }
    node = FindInOrder(_root -> m_right, _predicate, _context);
    if (node != NULL)
    {
        return node;
    }
    return NULL;
}




static void FreeTree(Node *_root, void (*_destroyer)(void*))
{
    if (_root == NULL)
    {
        return;
    }
    FreeTree(_root -> m_left, _destroyer);
    FreeTree(_root -> m_right, _destroyer);
    if (_destroyer != NULL)
    {
        _destroyer(_root);
    }
    free(_root);
}

static Node* HandleIfFirst(Node *_root, void *_data)
{
    Node *node;
    if (_root -> m_left == NULL)
    {
        node = CreateNode(_data);
        _root -> m_left = node;
        node -> m_father = node;
        return node;
    }
    return NULL;
}

static Node* CreateNode(void *_data)
{
    Node *newNode = (Node *) malloc (sizeof (Node));
    if (newNode == NULL)
    {
        return NULL;
    }
    newNode -> m_data = _data;
    newNode -> m_left = NULL;
    newNode -> m_father = NULL;
    newNode -> m_right = NULL;
    newNode -> m_next = NULL;
    newNode -> m_prev = NULL;
    return newNode;
}



static Node *PlaceToInsert(Node *_root ,void* _data, LessComparator _lessFunc, Node **_prev, Node **_next)
{
    Node *temp;
    *_next = NULL;
    *_prev = NULL;
    while (_root != NULL)
    {
        if (_lessFunc(_data, _root -> m_data))
        {
            temp = _root;
            *_next = temp;
            _root = _root -> m_left;
        }
        else if (_lessFunc(_root -> m_data, _data))
        {
            temp = _root;
            *_prev = temp;
            _root = _root -> m_right;
        }
        else
        {
            return NULL;
        } 
    }
    return temp;
}

static Node* PutNode(Node *_father, LessComparator _lessFunc, void *_data)
{
    Node *newNode;
    if (_father == NULL)
    {
        return NULL;
    }
    newNode = CreateNode(_data);
    if (_lessFunc(_data, _father -> m_data))
    {
        newNode -> m_father = _father;
        _father -> m_left = newNode;
        _father -> m_prev = newNode;
    }
    else
    {
        newNode -> m_father = _father;
        _father -> m_right = newNode;
        _father -> m_next = newNode;
    }
    return newNode;
}


static BSTreeItr ForEachInOrder(Node *_root, ActionFunction _action, void* _context)
{
    BSTreeItr node = NULL;
    if (_root == NULL)
    {
        return NULL;
    }
    node = ForEachInOrder(_root -> m_left, _action, _context);
    if (node != NULL)
    {
        return node;
    }
    if (_action(_root -> m_data, _context) == 0)
    {
        return (BSTreeItr) _root;
    }
    node = ForEachInOrder(_root -> m_right, _action, _context);
    if (node != NULL)
    {
        return node;
    }
    return (BSTreeItr) node;
}



static BSTreeItr ForEachPreOrder(Node *_root, ActionFunction _action, void* _context)
{
    BSTreeItr node = NULL;
    if (_root == NULL)
    {
        return NULL;
    }
    if (_action(_root -> m_data, _context) == 0)
    {
        return (BSTreeItr) _root;
    }
    node = ForEachPreOrder(_root -> m_left, _action, _context);
    if (node != NULL)
    {
        return node;
    }
    node = ForEachPreOrder(_root -> m_right, _action, _context);
    if (node != NULL)
    {
        return node;
    }
    return (BSTreeItr) node;
}


static BSTreeItr ForEachPostOrder(Node *_root, ActionFunction _action, void* _context)
{
    BSTreeItr node = NULL;
    if (_root == NULL)
    {
        return NULL;
    }
    node = ForEachPostOrder(_root -> m_left, _action, _context);
    if (node != NULL)
    {
        return node;
    }
    
    node = ForEachPostOrder(_root -> m_right, _action, _context);
    if (node != NULL)
    {
        return node;
    }
    if (_action(_root -> m_data, _context) == 0)
    {
        return (BSTreeItr) _root;
    }
    return (BSTreeItr) node;
}


static int CheckIfLeaf(BSTreeItr _itr)
{
    if (((Node *)_itr) -> m_left == NULL && ((Node *)_itr) -> m_right == NULL)
    {
        if(((Node *)_itr) -> m_right -> m_father == ((Node *)_itr) -> m_right)
        {
            return 1;
        }
        return 0;
    }
    return 0;
}
























