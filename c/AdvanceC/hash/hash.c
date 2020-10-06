#include <stdlib.h>
#include "HashMap.h"
#include "list.h"
#include "iter.h"
#include "listfunctions.h"
#define MAGIC_NUMBER 0XBEEFCAFE
#define UN_MAGIC_NUMBER 0XCAFEBABE



typedef struct Pair
{
    const void *m_key;
    const void *m_data;
}Pair;


struct HashMap
{
    size_t m_magicNumber;
    void **m_hashArr;
    size_t m_capacity;
    HashFunction m_hashFunction;
    EqualityFunction m_keysEqualFunc;
};

typedef struct FuncsContext
{
    KeyValueActionFunction m_action;
    void * m_key;

}FuncsContext;


#define CHECK_HASH(map) (_map == NULL || map-> m_magicNumber != MAGIC_NUMBER) ? MAP_UNINITIALIZED_ERROR : MAP_SUCCESS

#define HASH_FUNC(x, map) ((map -> m_hashFunction)(x) % map -> m_capacity) 


/*======================================== static function =================================*/

static MapResult CheckParaInsert(const void* _key, const void* _value);

static Pair *CreatePair(const void* _key, const void* _value);


static void DestroyPair(Pair *_pair);

static ListItr FindIter(List *_list, const void* _searchKey, const HashMap* _map);

/*==========================================================================================*/


HashMap* HashMapCreate(size_t _capacity, HashFunction _hashFunc, EqualityFunction _keysEqualFunc)
{
    HashMap *hashMap;
    void **hashArr;
    if (_capacity == 0 || _hashFunc == NULL || _keysEqualFunc == NULL)
    {
        return NULL;
    }
    hashArr = (void **) calloc (_capacity ,sizeof(void *));
    if (hashArr == NULL)
    {
        return NULL;
    }
    hashMap = (HashMap *) malloc (sizeof(HashMap));
    if (hashMap == NULL)
    {
        free(hashArr);
        return NULL;
    }

    hashMap -> m_magicNumber = MAGIC_NUMBER;
    hashMap -> m_hashArr = hashArr;
    hashMap -> m_hashFunction = _hashFunc;
    hashMap -> m_keysEqualFunc = _keysEqualFunc;
    hashMap -> m_capacity = _capacity;
    return hashMap;
}



MapResult HashMapInsert(HashMap* _map, const void* _key, const void* _value)
{
    ListItr end = NULL;
    ListItr begin = NULL;
    ListItr itr = NULL;
    MapResult status;
    Pair *pair = NULL;
    size_t hashInd;
    
    if(CHECK_HASH(_map))
    {
    	return MAP_UNINITIALIZED_ERROR;
    }
    if ((status = CheckParaInsert(_key, _value)) != MAP_SUCCESS)
    {
        return status;
    }

    if ((pair = CreatePair(_key, _value)) == NULL)
    {
        return MAP_ALLOCATION_ERROR;
    }
	
    hashInd = HASH_FUNC(_key, _map);
	begin = ListItrBegin(_map -> m_hashArr[hashInd]);
    end = ListItrEnd(_map -> m_hashArr[hashInd]);
	itr = ListItrFindFirst(begin, end, (PredicateFunction)(_map -> m_keysEqualFunc), pair);
	if(ListItrEquals(itr, end))
	{
		_map -> m_hashArr[hashInd] = ListCreate();
	}

    ListItrInsertBefore(end,pair);
    return MAP_SUCCESS;
}


MapResult HashMapRemove(HashMap* _map, const void* _searchKey, void** _pKey, void** _pValue)
{
	ListItr end = NULL;
    ListItr begin = NULL;
    Pair *data = NULL;
    ListItr itr;
    size_t key;
    if(CHECK_HASH(_map))
    {
    	return MAP_UNINITIALIZED_ERROR;
    }
    key = HASH_FUNC(_pKey, _map);
    begin = ListItrBegin(_map -> m_hashArr[key]);
    end = ListItrEnd(_map -> m_hashArr[key]);
    itr = ListItrFindFirst(begin, end, (PredicateFunction) (_map -> m_keysEqualFunc),(void *) _searchKey);
    data = (Pair*)ListItrRemove(itr);
    
    *_pKey 	 =  (void*)(data -> m_key);
    *_pValue =  (void*)(data -> m_data);
    
    DestroyPair(data);
    return MAP_SUCCESS;
}


MapResult HashMapFind(const HashMap* _map, const void* _searchKey, void** _pValue)
{
  	ListItr itr;
    size_t key;
    if (_map == NULL || _searchKey == NULL)
    {
         return MAP_KEY_NULL_ERROR;
    }
    key = _map -> m_hashFunction(_searchKey);
    itr = FindIter(_map -> m_hashArr[key], _searchKey, _map);
    if (itr == NULL)
    {
    	return MAP_KEY_NULL_ERROR;
    }
    return MAP_SUCCESS;
}

size_t HashMapSize(const HashMap* _map)
{
    size_t counter = 0;
    size_t index = 0;
    if (_map == NULL || _map -> m_magicNumber != MAGIC_NUMBER)
    {
        return 0;
    }
    for( ; index < _map -> m_capacity; index++)
    {
        if (_map -> m_hashArr[index] != NULL)
        {
            counter = counter + ListSize(_map -> m_hashArr[index]);
        }
    }
    return counter;
}

size_t HashMapForEach(const HashMap* _map, KeyValueActionFunction _action, void* _context)
{

    size_t NumOfBuc = 0;
    size_t index = 0;
    if (_map == NULL || _action == NULL)
    {
        return 0;
    }
    for( ; index < _map -> m_capacity; index++)
    {
        if (_map -> m_hashArr[index] != NULL)
        {
            NumOfBuc++;
        }
    }
    return 0;
}




/*================================================ aux functions ========================================*/



static Pair *CreatePair(const void* _key, const void* _value) 
{
    Pair *pair =  (Pair *) malloc (sizeof (Pair));
    if (pair == NULL)
    {
        return NULL;
    }
    pair -> m_data = _value;
    pair -> m_key = _key;
    return pair;
}


static void DestroyPair(Pair *_pair)
{
    free(_pair);
}



static ListItr FindIter(List *_list,const void* _searchKey, const HashMap* _map)
{
    ListItr first = NULL;
    ListItr begin = NULL;
    ListItr end = NULL;
    begin = ListItrBegin(_list);
    end = ListItrEnd(_list);
    first = ListItrFindFirst(begin, end,  (ListActionFunction) _map -> m_keysEqualFunc,(void *) _searchKey);
    return first;
}







static MapResult CheckParaInsert(const void* _key, const void* _value)
{
    if (_key == NULL)
    {
        return MAP_KEY_NULL_ERROR;
    }
    if (_value == NULL)
    {
        return MAP_NULL_VALUE;
    }
    return MAP_SUCCESS;
}



































