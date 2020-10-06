
#include <stdlib.h>
#include "../include/HashMap.h"
#include "../include/list.h"
#include "../include/iter.h"
#include "../include/listfunctions.h"
#include <stdio.h>
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





/*============================== tests ===========================*/

void testHashMapCreate();

void testHashMapInsert();


/*================================================================*/








int main()
{
    testHashMapCreate();
    testHashMapInsert();
    return 0;
}



size_t hashFunc(const void *_id)
{
    return *(int*)_id % 21;
}

 
int KeysEqual(const void *_a, const void *_b)
{
    if (*(int*)_a == *(int*)_b)
    {
        return 1;
    }
    return 0;
}

void testHashMapCreate()
{
    HashMap *hash;
    hash = HashMapCreate(20, hashFunc, KeysEqual);
    PRINT_TEST(hash != NULL);
}

void testHashMapInsert()
{
    HashMap *hash;
    int a = 5;
    int b = 54;
    int c = 5;
    int d = 34;
    int e = 5;
    int f = 85;
    int g = 5;
    int h = 34;
    hash = HashMapCreate(20, hashFunc, KeysEqual);
    HashMapInsert(hash, &b, &a);
    HashMapInsert(hash, &c, &d);
    HashMapInsert(hash, &e, &f);
    HashMapInsert(hash, &g, &h);
    PRINT_TEST(hash != NULL);
}






















