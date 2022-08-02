#ifndef UARTCOMMUNICATION_H
#define UARTCOMMUNICATION_H

#include <stdint.h>
#include "viscaCommands.h"

/*!
 * \brief Class for UART communication - intended mainly for VISCA prtocol
 */
class UartCommunication
{
public:
    UartCommunication(const char* device_path);
    ~UartCommunication();

    bool sendMessageArr(uint8_t* message, uint8_t size);

    template<typename... types>
    bool sendMessage(types... data){
        const uint8_t size = sizeof...(data);
        uint8_t message[] = { static_cast<uint8_t>(data)...};
        return sendMessageArr(message, size);
    }

    bool receiveMessage(uint8_t *data, int size, int waitMs = 0);
    bool loadMessageToBuffer(int size = MAX_BUFFER_SIZE, int waitMs = 0);

private:
    int m_descriptor;

    static const uint8_t TERMINATOR = 0xFF;

    static const int MAX_BUFFER_SIZE = 512;
    static const int USECONDS_PER_CHECK = 10000;

    uint8_t m_buffer[MAX_BUFFER_SIZE] {};
};

#endif // UARTCOMMUNICATION_H
