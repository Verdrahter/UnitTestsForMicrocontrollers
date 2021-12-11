#include "unity.h"
#include "UartCom.h"
#include "unity_runner/UnityRunner.h"

void setUp()
{
}

void tearDown()
{
}

int main(void)
{
#ifndef UNITY_INCLUDE_CONFIG_H
    static_assert(false, "define UNITY_INCLUDE_CONFIG_H in project - otherwise unity_config.h will not be used by unity")
#endif

    UartCom::Init();
    for(;;)
    {
        UartCom::Send("\n\rUnit testing with unity");
        UnityRunner::RunUnitTest();
        UartCom::Send("\n\rUnit tests performed");
        UartCom::GetChar();
    }

    return 0;
}
