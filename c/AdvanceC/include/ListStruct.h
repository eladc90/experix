#ifndef __LISTSTRUCT_H__
#define __LISTSTRUCT_H__

#include <stdlib.h>
typedef struct Node Node;

Node createNode(void _item);

struct Node
{
	void* m_data;
	Node* m_next;
	Node* m_prev;
};

struct List
{
	Node m_head;
	Node m_tail;
	size_t m_magicNumber;
};

#endif /* __LISTSTRUCT_H__*/
