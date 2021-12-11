#include "unity.h"


void test_one_is_not_two()
{
    TEST_ASSERT_EQUAL_INT(1, 2);
}


void test_one_is_one()
{
    TEST_ASSERT_EQUAL_INT(1, 1);
}


