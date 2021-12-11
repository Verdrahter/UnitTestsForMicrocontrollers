#pragma once

#include "unity.h"
#include "unit_tests/test1.h"

class UnityRunner
{
public:
    static void RunUnitTest()
    {
        UNITY_BEGIN();
        RUN_TEST(test_one_is_not_two);
        RUN_TEST(test_one_is_one);
        UNITY_END();
    }
};

