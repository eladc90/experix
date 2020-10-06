#include "myMalloc.h"
#include "../include/mu_test.h"

UNIT(testPositive)
 	void *test = NULL;
	Pool *pool = NULL;
	pool = MyMallocCreate(10);
	ASSERT_THAT(pool != NULL);
	test = MyMalloc(pool, 3);
	ASSERT_THAT(test != NULL);
	test = MyMalloc(pool, 3);
	ASSERT_THAT(test != NULL);
	test = MyMalloc(pool, 3);
	ASSERT_THAT(test != NULL);
END_UNIT

TEST_SUITE(framework test)
	TEST(testPositive)
END_SUITE
