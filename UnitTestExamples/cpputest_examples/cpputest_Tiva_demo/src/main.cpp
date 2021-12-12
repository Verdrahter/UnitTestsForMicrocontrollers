#include "CppUTest/TestHarness.h"
#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/PlatformSpecificFunctions.h"
#include "UartCom.h"


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

int UartPutchar(int c)
{
    UartCom::Send(static_cast<char>(c));
    if (c=='\n')
        UartCom::Send('\r');
}

/**
 * main
 */
int main(void)
{
    PlatformSpecificPutchar = UartPutchar;

    char av = '\0';
    char *pav = &av;

    UartCom::Init();
    for(;;)
    {
        UartCom::SendString("\n\rUnit testing with CppUTest\n");
        RUN_ALL_TESTS(0, &pav);
        UartCom::SendString("\n\rUnit tests performed, #");
        PrintIncrementedNumber();
        UartCom::GetChar();
    }
}
