#include <stdint.h>
#include <stdbool.h>
#include <string.h>
extern "C"
{
#include "inc/hw_memmap.h"
#include "inc/hw_uart.h"
#include "inc/hw_types.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
}
#include "UartCom.h"

#define NUM_UART_DATA    4

//*****************************************************************************
//
// Send a string to the UART.  This function sends a string of characters to a
// particular UART module.
//
//*****************************************************************************
void
UARTSend(uint32_t ui32UARTBase, const uint8_t *pui8Buffer, uint32_t ui32Count)
{
    //
    // Loop while there are more characters to send.
    //
    while(ui32Count--)
    {
        //
        // Write the next character to the UART.
        //
        MAP_UARTCharPut(ui32UARTBase, *pui8Buffer++);
    }
}

void UartCom::Init()
{
    static bool initialised { false };
    if (initialised)
        return;
    initialised = true;

    uint32_t ui32SysClock;

    //
    // Set the clocking to run directly from the crystal.
    //
    //
    // Run from the PLL at 120 MHz.
    // Note: SYSCTL_CFG_VCO_240 is a new setting provided in TivaWare 2.2.x and
    // later to better reflect the actual VCO speed due to SYSCTL#22.
    //
    ui32SysClock = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
            SYSCTL_OSC_MAIN |
            SYSCTL_USE_PLL |
            SYSCTL_CFG_VCO_240), 120000000);


    //
    // Enable the peripherals used by this example.
    // UART0 :  To dump information to the console about the example.
    // UART7 :  Enabled in loopback mode. Anything transmitted to Tx will be
    //          received at the Rx.
    //
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART7);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Set GPIO A0 and A1 as UART pins.
    //
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    MAP_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Internal loopback programming.  Configure the UART in loopback mode.
    //
    UARTLoopbackEnable(UART7_BASE);

    //
    // Configure the UART for 115,200, 8-N-1 operation.
    //
    MAP_UARTConfigSetExpClk(UART0_BASE, ui32SysClock, 115200,
                            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                                    UART_CONFIG_PAR_NONE));
    MAP_UARTConfigSetExpClk(UART7_BASE, ui32SysClock, 115200,
                            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                                    UART_CONFIG_PAR_NONE));

}

bool UartCom::IsUartBusy()
{
    return MAP_UARTBusy(UART0_BASE);
}

void UartCom::Send(uint8_t const* pBuffer, uint32_t byteNum)
{
    //
    // Display the data received, after loopback, over UART's receive FIFO.
    //
    UARTSend(UART0_BASE, pBuffer, byteNum);
}

int32_t UartCom::GetChar()
{
    return UARTCharGet(UART0_BASE);
}
