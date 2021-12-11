#pragma once

#include "unity.h"
#include "unit_tests/test1.h"

class UnityRunner
{
public:
    /**
     * Run the unit tests
     */
    static void RunUnitTest()
    {
        UNITY_BEGIN();
        EnumerateThroughTests();
        UNITY_END();
    }

private:
    /**
     * Edit this method to include the unit tests
     */
    static void EnumerateThroughTests()
    {
        RUN_TEST(test_one_is_not_two);
        RUN_TEST(test_one_is_one);
    }
};

