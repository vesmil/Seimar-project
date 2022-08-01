#ifndef VISCACOMMUNICATION_H
#define VISCACOMMUNICATION_H

#include <unistd.h>
#include "global/logCategories.h"

class ViscaCommunication
{
public:
    ViscaCommunication(const char* device_path);

    template<uint8_t... data>
    bool sendMessage(){
        if (m_descriptor == -1)
        {
            qCWarning(viscaWarning()) << "Visca::sendBytes(): Error, UART port is closed!";
            return false;
        }

        uint8_t size = sizeof...(data) + 1;
        uint8_t message[size] = { data..., 0xFF};

        return sendMessage(message, size);
    }

    bool sendMessage(uint8_t* message, int size);
    bool receiveMessage(uint8_t *data, int size, int waitMs = 0);
    bool LoadMessageToPrivateBuffer(int size, int waitMs = 0);

private:
    bool setAddress();
    bool clearIF();

    int m_descriptor;

    static const uint16_t MAX_BUFFER_SIZE = 512;
    uint8_t m_buffer[MAX_BUFFER_SIZE];
};

#endif // VISCACOMMUNICATION_H
