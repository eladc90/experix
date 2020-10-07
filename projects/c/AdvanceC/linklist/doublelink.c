#include <stdio.h>
#include <stdlib.h>
#include "liststruct.h"
#include "list.h"
#include <assert.h>


#define MAGIC_NUMBER 549871345
#define EMPTY 0
#define NOT_EMPTY 1


/* =================================== static functions ====================================*/

static void insert(Node *_new, List *_list);

static void removeTail(List * _list);

static void removeHead(List *_list);

static void insertTail(Node *_new, List *_list);

/* =========================================================================================*/




List* ListCreate(void)
{
	List *linkAdress;
	linkAdress = (List *) malloc (sizeof(List));
	if (linkAdress == NULL)
	{
		return NULL;
	}

	linkAdress -> m_head.m_next = &(linkAdress -> m_tail);
	linkAdress -> m_tail.m_prev = &(linkAdress -> m_head);
	linkAdress -> m_head.m_prev = &(linkAdress -> m_head);
	linkAdress -> m_tail.m_next = &(linkAdress -> m_tail);
	linkAdress -> m_magicNumber = MAGIC_NUMBER;
	return linkAdress;
}

void ListDestroy(List** _pList, void (*_elementDestroy)(void* _item))
{
	Node *temp;
	if (_pList == NULL || *_pList  == NULL || (*_pList) -> m_magicNumber != MAGIC_NUMBER)
	{
		return;
	}
	(*_pList) -> m_magicNumber = 0; 
	
	while( ((*_pList)->m_head.m_next) != &((*_pList)->m_tail))
	{
		temp = (*_pList) -> m_head.m_next;

		if (_elementDestroy != NULL)
		{
			_elementDestroy((*_pList) -> m_head.m_next -> m_data);
		}

		(*_pList)->m_head.m_next = temp->m_next;
		free(temp);
	}
	free(*_pList);
	*_pList = NULL;
	return;
}




List_Result ListPushHead(List* _list, void* _item)
{
	Node *newNode;
	if (_list == NULL)
	{
		return LIST_ERR_NULL;
	}
	if (_item == NULL)
	{
		return LIST_NULL_ELEMENT_ERROR;
	}
	newNode = (Node *) malloc (sizeof(Node));
	if (newNode == NULL)
	{
		return LIST_ERR_NULL;
	}
	newNode -> m_data = _item;
	insert (newNode, _list);
	return LIST_SUCCESS;
}



List_Result ListPushTail(List* _list, void* _item)
{
	Node *newNode;
	if (_list == NULL)
	{
		return LIST_ERR_NULL;
	}
	if (_item == NULL)
	{
		return LIST_NULL_ELEMENT_ERROR;
	}
	newNode = (Node *) malloc (sizeof(Node));
	
	if (newNode == NULL)
	{
		return LIST_ERR_NULL;
	}
	newNode -> m_data = _item;
	insertTail (newNode, _list);
	return LIST_SUCCESS;
}




List_Result ListPopHead(List* _list, void** _pItem)
{
	if (_list == NULL || _pItem == NULL)
	{
		return LIST_ERR_NULL;
	}
	if (_list -> m_head.m_next == &(_list -> m_tail))
	{
		return LIST_ERR_UNDERFLOW;
	}
	*_pItem = _list -> m_head.m_next -> m_data;
	removeHead (_list);
	return LIST_SUCCESS;
}



List_Result ListPopTail(List* _list, void** _pItem)
{
	if (_list == NULL || _pItem == NULL)
	{
		return LIST_ERR_NULL;
	} 
	if (_list -> m_head.m_next == &(_list -> m_tail))
	{
		return LIST_ERR_UNDERFLOW;
	}
	*_pItem = _list -> m_tail.m_prev -> m_data;
	removeTail (_list);
	return LIST_SUCCESS;
}



size_t ListSize(const List* _list)
{
	Node *temp = _list->m_head.m_next;
	size_t count = 0;
	if (_list != NULL)
	{
		while( temp != &(_list->m_tail) )
		{
			temp = temp -> m_next;
			count++;
		}
	}
	return count;
}

Node *createNode(void* _item)
{
	Node* newNode;
	newNode = (Node *) malloc (sizeof (Node));
	if (newNode == NULL)
	{
		return NULL;
	}
	newNode -> m_data = _item;
	return newNode;
}





/*============================================= aux functions ===========================================*/

static void removeHead(List *_list)
{
	(_list -> m_head.m_next -> m_next -> m_prev) = &(_list -> m_head);
	_list -> m_head.m_next = (_list -> m_head.m_next -> m_next);
}

static void removeTail(List * _list)
{
	(_list -> m_tail.m_prev -> m_prev -> m_next) = &(_list -> m_tail);
	_list -> m_tail.m_prev = (_list -> m_tail.m_prev -> m_prev);
}

static void insert(Node *_new, List *_list)
{
	_new -> m_next = _list -> m_head.m_next;
	(_new -> m_next -> m_prev) = _new;
	_list -> m_head.m_next = _new;
	_new -> m_prev = &(_list -> m_head);
}

static void insertTail(Node *_new, List *_list)
{
	_new -> m_prev = _list -> m_tail.m_prev;
	_list -> m_tail.m_prev = _new;
	_new -> m_next = &(_list -> m_tail);
	(_new -> m_prev -> m_next) = _new;
}














