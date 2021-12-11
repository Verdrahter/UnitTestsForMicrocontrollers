/*
 * RunUart.h
 *
 *  Created on: 11.12.2021
 *      Author: BG
 */

#pragma once
#include <type_traits>


class UartCom
{
public:
    static void Init();

    static bool IsUartBusy();

    static void WaitForUart();

    template<typename T>void static Send(T const& dataArray, uint32_t byteNum);

    template<typename T>void static Send(T const data[]);

    template<typename T>void static Send(T const& data);

    static int32_t GetChar();

private:
    static void Send(uint8_t const* pBuffer, uint32_t byteNum);
};

inline void UartCom::WaitForUart()
{
    //
    // Wait for the UART module to complete transmitting.
    //
    while (IsUartBusy())
    {
    }
}

template<typename T>void UartCom::Send(T const& dataArray, uint32_t byteNum)
{
    static_assert(std::is_array<T>::value, "");

    auto size = byteNum < sizeof(T) ? byteNum : sizeof(T);
    Send(reinterpret_cast<const uint8_t*>(dataArray), size);
}

template<typename T>void UartCom::Send(T const data[])
{
    static_assert(!std::is_pointer<T>::value, "");
    static_assert(!std::is_array<T>::value, "");

    Send(reinterpret_cast<uint8_t const*>(data), sizeof(T));
}

template<typename T>void UartCom::Send(T const& data)
{
    static_assert(!std::is_pointer<T>::value, "");
    static_assert(!std::is_array<T>::value, "");

    Send(reinterpret_cast<uint8_t const*>(&data), sizeof(T));
}
