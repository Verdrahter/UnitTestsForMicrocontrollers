#include "unity.h"


/**
 * This will fail
 */
void test_one_is_not_two()
{
    TEST_ASSERT_EQUAL_INT(1, 2);
}

/**
 * This will succeed
 */
void test_one_is_one()
{
    TEST_ASSERT_EQUAL_INT(1, 1);
}


