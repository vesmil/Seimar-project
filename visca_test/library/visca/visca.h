#ifndef VISCA_H
#define VISCA_H

#include "library/visca/uartCommunication.h"
#include "global/logCategories.h"

#include <algorithm>

/*!
 * \brief Class with basic VISCA commands - facade on UartCommunication class
 */
class Visca
{
public:
    Visca(const char* device_path);

    template <std::size_t replySize = 4, std::size_t size>
    bool executeCommand(const std::array<uint8_t, size>&& data, int waitTime = SHORT_WAIT_TIME_MS, const QString &logMessage = QString{})
    {
        std::array<uint8_t, replySize> reply {};
        if (!m_uart.sendMessage(m_camAddr, data) || !m_uart.receiveMessage(reply, waitTime) || !checkReply(reply))
        {
            if (logMessage.length() > 0)
                qCInfo(viscaLog()) << logMessage << "- unsuccessful.";

            return false;
        }

        if (logMessage.length() > 0)
            qCInfo(viscaLog()) << logMessage << "- successful.";

        return true;
    }

    template <std::size_t replySize, std::size_t size, typename T>
    T inquireCommand(const std::array<uint8_t, size>&& data, T (*processReply)(std::array<uint8_t, replySize>) = &checkReply<replySize>, int waitTime = SHORT_WAIT_TIME_MS)
    {
        m_uart.sendMessage(m_camAddr, data);

        std::array<uint8_t, replySize> reply {};
        if (!m_uart.receiveMessage(reply, waitTime))
        {
            qCInfo(viscaLog()) << "Failed to inquire";
            return {};
        }

        // TODO debug
        return processReply(reply);
    }

private:    
    bool setAddress();
    bool clearIF();

    //! \brief prints errors contained in a reply to log
    //! \return boolean if the reply was without any errors
    template <std::size_t size>
    static bool checkReply(std::array<uint8_t, size>& reply)
    {
        if (size <= 2)
        {
                qCWarning(viscaLog()) << "Reply is too short.";
                return false;
        }

        if ((reply[1] & 0xF0) == 0x60)
        {
            printReplyError((err) reply[2]);
            return false;
        }

        return true;
    }

    enum err  : uint8_t { LENGTH = 0x01, SYNTAX = 0x02, BUFULL = 0x03, CANCEL = 0x04, SOCKET = 0x05, EXECUT = 0x06 };

    ///! \brief used as complemenatry function for checkReply
    static void printReplyError(err code);

    UartCommunication m_uart;
    uint8_t m_camAddr;

    static const int INIT_TRIES_COUNT = 10;
    static const int DEFAULT_USLEEP_WAIT = 50000;

    static const int SHORT_WAIT_TIME_MS = 400; // TODO mby remake to BASE_WAIT_TIME
    static const int LONG_WAIT_TIME_MS = 400;

    enum addr : uint8_t { BROADCAST = 0x88, CAM_BASE = 0x80};
};

#endif // VISCA_H
