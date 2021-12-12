#include "CppUTest/TestHarness.h"

TEST_GROUP(SampleTestGroup)
{
};


/**
 * This will fail
 */
TEST(SampleTestGroup, test_one_is_not_two)
{
    CHECK_EQUAL(1, 2);
}

/**
 * This will succeed
 */
TEST(SampleTestGroup, test_one_is_one)
{
    CHECK_EQUAL(1, 1);
}


