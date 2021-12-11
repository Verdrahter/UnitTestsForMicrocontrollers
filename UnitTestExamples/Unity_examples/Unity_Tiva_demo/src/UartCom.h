#pragma once
#include <type_traits>


/**
 * Class for UART communication with PC (e.g. using the Terminal in Code Composer Studio)
 * Just a paste&copy implementation using an example from the TivaWare. Used with launchpad TM4C1294XL
 */
class UartCom
{
public:
    static void Init();

    static bool IsUartBusy();

    static void WaitForUart();

    template<typename T>void static Send(T const& dataArray, uint32_t byteNum);

    template<typename T>void static SendString(T const& data);

    template<typename T>void static Send(T const& data);

    static int32_t GetChar();

private:
    static void Send(uint8_t const* pBuffer, uint32_t byteNum);
};

inline void UartCom::WaitForUart()
{
    while (IsUartBusy())
    {
    }
}

template<typename T>void UartCom::Send(T const& dataArray, uint32_t byteNum)
{
    static_assert(!std::is_pointer<T>::value, "");
    static_assert(std::is_array<T>::value, "");

    auto size = byteNum < sizeof(T) ? byteNum : sizeof(T);
    Send(reinterpret_cast<const uint8_t*>(dataArray), size);
}

template<typename T>void UartCom::SendString(T const& data)
{
    static_assert(!std::is_pointer<T>::value, "");
    static_assert(std::is_array<T>::value, "");

    Send(reinterpret_cast<uint8_t const*>(data), sizeof(data));
}

template<typename T>void UartCom::Send(T const& data)
{
    static_assert(!std::is_pointer<T>::value, "");
    static_assert(!std::is_array<T>::value, "");

    Send(reinterpret_cast<uint8_t const*>(&data), sizeof(T));
}
