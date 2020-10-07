#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "liststruct.h"
#define EQUAL 1
#define NOT_EQUAL 0
#define MAGIC_NUMBER 549871345


struct ListItr
{
	Node* ListItr;
};

static Node g_wrongNode;
	
ListItr g_wrongItr = &g_wrongNode;







ListItr ListItrBegin(const List* _list)
{
	if (_list == NULL)
	{
		return g_wrongItr;
	}
    return _list -> m_head.m_next;
}



ListItr ListItrEnd(const List* _list)
{
	if (_list == NULL)
	{
		return g_wrongItr;
	}
    return &(((List *)_list) -> m_tail);
}

int ListItrEquals(const ListItr _a, const ListItr _b)
{
	if (_a == NULL || _b == NULL)
	{
		return 0;
	}
	if (_a == _b)
	{
		return 1;
	}
	return 0;
}

ListItr ListItrNext(ListItr _itr)
{
	if (_itr == NULL)
	{
		return NULL;
	}
	if (_itr -> m_next -> m_next == _itr -> m_next)
	{
		return _itr -> m_next;
	}
	return _itr -> m_next -> m_next -> m_prev;
}


ListItr ListItrPrev(ListItr _itr)
{
	if (_itr == NULL)
	{
		return NULL;
	}
	if (_itr -> m_prev -> m_prev == _itr)
	{
		return _itr;
	}
	return _itr -> m_prev -> m_prev -> m_next;
}

void* ListItrGet(ListItr _itr)
{
	if (_itr == NULL)
	{
		return NULL;
	}
	return _itr -> m_data;
}


void* ListItrSet(ListItr _itr, void* _element)
{
	if (_itr == NULL || _element == NULL || _itr -> m_next == _itr || _itr -> m_prev == _itr)
	{
		return NULL;
	}
	return _itr -> m_data = _element;
}

ListItr ListItrInsertBefore(ListItr _itr, void* _element)
{
	Node *newNode = createNode(_element);
	if (_itr == NULL || _element == NULL)
	{
		return NULL;
	}
	newNode -> m_next = _itr;
	newNode -> m_prev = _itr -> m_prev;
	_itr -> m_prev -> m_next = newNode;
	_itr -> m_prev = newNode;
	return newNode;
}


void* ListItrRemove(ListItr _itr)
{
	void *temp;
	if (_itr == NULL || _itr == _itr -> m_next)
	{
		return NULL;
	}
	_itr -> m_prev -> m_next = _itr -> m_next;
	_itr -> m_next -> m_prev = _itr -> m_prev;
	temp = _itr -> m_data;
	free(_itr);
	return temp;
}





















