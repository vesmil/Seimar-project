#ifndef UARTCOMMUNICATION_H
#define UARTCOMMUNICATION_H

#include <unistd.h>
#include "global/logCategories.h"

/*!
 * \brief Class for UART communication - intended for VISCA prtocol
 */
class UartCommunication
{
public:
    UartCommunication(const char* device_path);

    static const uint8_t TERMINATOR = 0xFF;

    bool sendMessage(uint8_t* message, int size);

    // TODO - runtime support

    /*
    template<typename... types>
    bool sendMessage(types... data){
        if (m_descriptor == -1)
        {
            qCWarning(viscaWarning()) << __PRETTY_FUNCTION__ << ":Error, port is closed!";
            return false;
        }

        uint8_t size = sizeof...(data) + 1;
        uint8_t message[size] = { data..., TERMINATOR};

        return sendMessage(message, size);
    }
    */

    template<uint8_t... data>
    bool sendMessage(){
        if (m_descriptor == -1)
        {
            qCWarning(viscaWarning()) << __PRETTY_FUNCTION__ << ":Error, port is closed!";
            return false;
        }

        uint8_t size = sizeof...(data) + 1;
        uint8_t message[size] = { data..., TERMINATOR};

        return sendMessage(message, size);
    }

    bool receiveMessage(uint8_t *data, int size, int waitMs = 0);
    bool LoadMessageToPrivateBuffer(int size, int waitMs = 0);

private:
    int m_descriptor;

    static const int MAX_BUFFER_SIZE = 256;
    static const int USECONDS_PER_CHECK = 10000;

    uint8_t m_buffer[MAX_BUFFER_SIZE];
};

#endif // UARTCOMMUNICATION_H
