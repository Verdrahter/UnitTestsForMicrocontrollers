#include "unity.h"
#include "UartCom.h"
#include "unity_runner/UnityRunner.h"
#include <stdio.h>


/**
 * This is just to have something changed in the output
 */
void PrintIncrementedNumber()
{
    static int i {};
    static char buf[2+sizeof(i)*10/3];
    sprintf(buf, "%d", ++i);
    UartCom::SendString(buf);
}


int main()
{
#ifndef UNITY_INCLUDE_CONFIG_H
    // refer to https://github.com/ThrowTheSwitch/Unity/blob/master/docs/UnityConfigurationGuide.md
    static_assert(false, "define UNITY_INCLUDE_CONFIG_H in project - otherwise unity_config.h will not be used by unity")
#endif

    UartCom::Init();
    for(;;)
    {
        UartCom::SendString("\n\rUnit testing with unity\n");
        UnityRunner::RunUnitTest();
        UartCom::SendString("\n\rUnit tests performed, #");
        PrintIncrementedNumber();
        UartCom::GetChar();
    }
}
