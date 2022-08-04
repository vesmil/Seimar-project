#ifndef UARTCOMMUNICATION_H
#define UARTCOMMUNICATION_H

#include <stdint.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "viscaCommands.h"
#include "global/logCategories.h"

/*!
 * \brief Class for UART communication - intended mainly for VISCA prtocol
 */
class UartCommunication
{
public:
    UartCommunication(const char* device_path);
    ~UartCommunication();

    template<std::size_t size>
    bool sendMessageArr(uint8_t addr, const std::array<uint8_t, size>& message)
    {
        if (m_descriptor == -1)
        {
            qCWarning(viscaLog()) << "Error, port is closed!";
            return false;
        }

        int sent_size = write(m_descriptor, &addr, 1);
        if (sent_size == -1)
        {
            qCWarning(viscaLog()) << "Error, UART sending error!";
            return false;
        }

        sent_size = write(m_descriptor, message.begin(), size);
        if (sent_size != size)
        {
            qCWarning(viscaLog()) << "Writing wasn't sucesful, sent" << sent_size + 1 << "out of" << size + 1 << "bytes";
            return false;
        }

        return true;
    }

    template<typename... types>
    bool sendMessage(uint8_t address, types... data)
    {
        const uint8_t size = sizeof...(data);
        std::array<uint8_t, size> message { static_cast<uint8_t>(data)...};

        return sendMessageArr(address, message);
    }

    template<std::size_t size>
    bool receiveMessage(std::array<uint8_t, size>& data, int waitMs)
    {
        if (m_descriptor == -1)
        {
            qCWarning(viscaLog()) << "Error, port is closed";
            return -1;
        }

        const int checkLoops = waitMs / 10 + 1;

        for (int i = 0; i < checkLoops; ++i)
        {
            if (ioctl(m_descriptor, FIONREAD) >= (int) size)
                break;

            usleep(USECONDS_PER_CHECK);
        }

        int read_count = read(m_descriptor, data.begin(), size);
        if (read_count != size && read_count < 3)
        {
            qCWarning(viscaLog()) << "Error, less than 3 bytes recieved!";
            return false;
        }

        return true;
    }

private:
    int m_descriptor;

    static const uint8_t TERMINATOR = 0xFF;
    static const int USECONDS_PER_CHECK = 10000;
};

#endif // UARTCOMMUNICATION_H
