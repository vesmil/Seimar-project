#ifndef UARTCOMMUNICATION_H
#define UARTCOMMUNICATION_H

#include <stdint.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <QString>

#include "global/logcategories.h"

/*!
 * \brief Class for UART communication - intended mainly to be used by Visca class
 * \note If used for different protocol it might require few changes
 */
class UartCommunication
{
public:
    explicit UartCommunication(const char* device_path);
    ~UartCommunication();

    /*!
     * \brief Sends array of bytes using (sys call) write to open UART port
     * \param data - array of bytes to send
     * \return true if sending was successful, false otherwise
     */
    template<std::size_t size>
    bool sendMessage(uint8_t addr, const std::array<uint8_t, size>& message)
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

    // NOTE function for simpler debug
    /*
    template<typename... types>
    [[deprecated("Use only for debug")]]
    bool sendMessage(uint8_t address, types... data)
    {
        const uint8_t size = sizeof...(data);
        std::array<uint8_t, size> message { static_cast<uint8_t>(data)...};

        return sendMessage(address, message);
    }
    */

    /*!
     * \brief Reads UART response and writes it to array
     * \param data - array to write response to
     * \return true if reading was successful, false otherwise
     * \details while less than waitMS has passed it periodically checks whether the response is ready...
     */
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

        /* NOTE used for printing the response
        {
            QString test;
            for (auto&& b : data)
                test += QString::number(b, 16) + " ";

            test.chop(1);
            qCInfo(viscaLog()).noquote() << test;
        }
        */

        return true;
    }

    /*!
     * \brief Reads UART response and writes them to throwaway array - used if out of sync with messages
     */
    void ClearReplies()
    {
        int read_count = read(m_descriptor, THROWAWAY_BUFFER, BUFFER_SIZE);
        qCInfo(viscaLog()).noquote() << "Throwing away" << read_count << "bytes";
    }

private:
    int m_descriptor;

    static const uint8_t TERMINATOR = 0xFF;
    static const int USECONDS_PER_CHECK = 10000;

    static const std::size_t BUFFER_SIZE = 512;
    uint8_t THROWAWAY_BUFFER[BUFFER_SIZE] {};
};

#endif // UARTCOMMUNICATION_H
