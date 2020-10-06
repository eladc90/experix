#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "iter.h"
#include "listfunctions.h"


static void BubbleSort(ListItr _begin, ListItr _end, LessFunction _less);

static void swap(void **a, void **b);



ListItr ListItrFindFirst(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context)
{
    if (_predicate == NULL || _context == NULL)
    {
        return NULL;
    }
    while (_begin != _end)
    {
        if (_predicate(ListItrGet(_begin) , _context) == 0 )
        {
            return _begin;
        }
        _begin = ListItrNext(_begin);
    }
    return _end;
}

ListItr ListItrForEach(ListItr _begin, ListItr _end, ListActionFunction _action, void* _context)
{
    if (_action == NULL || _context == NULL )
    {
        return NULL;
    }
        
    while (_begin != _end)
    {
        if (_action(ListItrGet(_begin) , _context) == 0 )
        {
            return _begin;
        }
        _begin = ListItrNext(_begin);
    }
    return _end;
}

void ListItrSort(ListItr _begin, ListItr _end, LessFunction _less)
{
    if (_less == NULL || _begin == NULL || _end == NULL)
    {
        return;
    }
    BubbleSort(_begin, _end, _less);
}


ListItr ListItrSplice(ListItr _dest, ListItr _begin, ListItr _end)
{
    void *data;
    ListItr temp;
    if (_dest == NULL || _begin == NULL || _end == NULL)
    {
        return NULL;
    }
    while (_begin != _end)
    {
        temp = _begin;
        data = ListItrGet(_begin);
        ListItrInsertBefore(_dest, data);
        _begin = ListItrNext(_begin);
        ListItrRemove(temp);
    }
    return _dest;
}

List* ListItrCut(ListItr _begin, ListItr _end)
{
    void *data;
    ListItr temp;
    List *list;
    if (_begin == NULL || _end == NULL)
    {
        return NULL;
    }
    list = ListCreate();
    while (_begin != _end)
    {
        temp = _begin;
        data = ListItrGet(_begin);
        ListPushHead(list, data);
        _begin = ListItrNext(_begin);
        ListItrRemove(temp);
    }
    return list;

}


static void BubbleSort(ListItr _begin, ListItr _end, LessFunction _less) 
{ 
   ListItr  j = _begin;
   void *dataA = NULL, *dataB = NULL; 
   while( _begin != _end)       
   {
        dataA = ListItrGet(j);
        j = ListItrNext(j);
        dataB = ListItrGet(j); 
      while(j != _end) 
        {
            if( (_less(dataA ,dataB)) == 1 )
            {
                swap(&dataA,&dataB);
            } 
            dataA = ListItrGet(j);
            j = ListItrNext(j);
            dataB = ListItrGet(j);
        }
        _begin = ListItrNext(_begin);
   }
}


static void swap(void **a, void **b)
{
    void *temp = *a;
    *a = *b;
    *b = temp;
} 