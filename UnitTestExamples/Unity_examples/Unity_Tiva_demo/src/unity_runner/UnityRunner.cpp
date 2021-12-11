#include "UnityRunner.h"
#include "unity_config.h"
#include "UartCom.h"

/**
 * Function is called by Unity. The call is activated by a #define
 * The character is send via UART to a terminal on the PC
 */
extern "C" void SendChar(char a)
{
    UartCom::Send(a);
    if (a == '\n')
        UartCom::Send('\r');
}

/**
 * Required by Unity
 */
void setUp()
{
}

/**
 * Required by Unity
 */
void tearDown()
{
}

