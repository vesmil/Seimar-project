#ifndef UARTCOMMUNICATION_H
#define UARTCOMMUNICATION_H

#include <stdint.h>

/*!
 * \brief Class for UART communication - intended mainly for VISCA prtocol
 */
class UartCommunication
{
public:
    UartCommunication(const char* device_path);
    ~UartCommunication();

    /*!
     * \brief Sends byte (uint8_t) array with appended 0xFF
     * \return bool if the operation was successful
     */
    bool sendMessage(uint8_t* message, const uint8_t size);

    /*!
     * \brief Sends byte (uint8_t) array created from variable number of params with appended 0xFF
     * \return bool if the operation was successful
     */
    template<typename... types>
    bool sendMessage(types... data){
        const uint8_t size = sizeof...(data) + 1;
        uint8_t message[] = { static_cast<uint8_t>(data)..., TERMINATOR};

        return sendMessage(message, size);
    }

    bool receiveMessage(uint8_t *data, int size, int waitMs = 0);
    bool LoadMessageToPrivateBuffer(int size, int waitMs = 0);

private:
    int m_descriptor;

    static const uint8_t TERMINATOR = 0xFF;
    static const int MAX_BUFFER_SIZE = 256;
    static const int USECONDS_PER_CHECK = 10000;

    uint8_t m_buffer[MAX_BUFFER_SIZE];
};

#endif // UARTCOMMUNICATION_H
