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

    template <std::size_t size>
    bool executeCommand(const std::array<uint8_t, size>&& data, int waitTime = SHORT_WAIT_TIME_MS, const QString &logMessage = QString{})
    {
        std::array<uint8_t, 4> reply;
        if (!m_uart.sendMessageArr(m_camAddr, data) || !m_uart.receiveMessage(reply, waitTime) || !checkReply(reply))
        {
            if (logMessage.length() > 0)
                qCInfo(viscaLog()) << logMessage << "- unsuccessful.";

            return false;
        }

        if (logMessage.length() > 0)
            qCInfo(viscaLog()) << logMessage << "- successful.";

        return true;
    }

private:    
    bool setAddress();
    bool clearIF();

    /*!
     * \brief prints errors contained in a reply to log
     * \return boolean if the reply was without any errors
     */
    template <std::size_t size>
    bool checkReply(std::array<uint8_t, size>& reply)
    {
        if (size < 2 )
        {
            qCWarning(viscaLog()) << "Reply is too short.";
            return false;
        }

        if ((reply[1] & 0xF0) == 0x60)
        {
            if (size == 2 )
            {
                qCWarning(viscaLog()) << "Reply doesn't provide any description.";
            }
            else
            {
                switch (reply[2])
                {
                    case err::LENGTH:
                        qCWarning(viscaLog()) << "Message length error";
                        break;
                    case err::SYNTAX:
                        qCWarning(viscaLog()) << "Syntax Error";
                        break;
                    case err::BUFULL:
                        qCWarning(viscaLog()) << "Command buffer full";
                        break;
                    case err::CANCEL:
                        qCWarning(viscaLog()) << "Command canceled";
                        break;
                    case err::SOCKET:
                        qCWarning(viscaLog()) << "No socket (to be canceled)";
                        break;
                    case err::EXECUT:
                        qCWarning(viscaLog()) << "Command not executable";
                        break;
                }
            }
            return false;
        }
        return true;
    }

    UartCommunication m_uart;
    uint8_t m_camAddr;

    static const int INIT_TRIES_COUNT = 10;
    static const int DEFAULT_USLEEP_WAIT = 50000;
    static const int SHORT_WAIT_TIME_MS = 200;
    static const int LONG_WAIT_TIME_MS = 400;

    static const uint8_t TERMINATOR = 0xFF;

    struct addr {
        static const uint8_t BROADCAST = 0x88;
        static const uint8_t CAM_BASE = 0x80;
    };

    // TODO remake as enum?
    struct err {
        static const uint8_t LENGTH = 0x01;
        static const uint8_t SYNTAX = 0x02;
        static const uint8_t BUFULL = 0x03;
        static const uint8_t CANCEL = 0x04;
        static const uint8_t SOCKET = 0x05;
        static const uint8_t EXECUT = 0x06;
    };
};

#endif // VISCA_H
