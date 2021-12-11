/*
 * UnityRunner.cpp
 *
 *  Created on: 11.12.2021
 *      Author: BG
 */

#include "UnityRunner.h"
#include "unity_config.h"
#include "UartCom.h"

extern "C" void SendChar(char a)
{
    UartCom::Send(a);
    if (a == '\n')
        UartCom::Send('\r');
}
