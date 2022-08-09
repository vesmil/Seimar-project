#ifndef VISCA_H
#define VISCA_H

#include "library/visca/uartCommunication.h"
#include "global/logCategories.h"

#include <algorithm>

/*!
 * \brief Class with basic VISCA commands - facade on UartCommunication class
 */
class Visca {
public:
    Visca(const char *device_path);

    // TODO write documentaion
    template<std::size_t replySize = 3, std::size_t size>
    bool executeCommand(const std::array <uint8_t, size> &&data,
                        int waitTime = SHORT_WAIT_TIME_MS,
                        QString &&logMessage = QString{})
    {
        if (logMessage.length() != 0)
            logMessage = "(" + logMessage + ")";

        if (!m_uart.sendMessage(m_camAddr, data))
        {
            qCInfo(viscaLog()).noquote() << "Failed sending" << logMessage;
            return false;
        }

        if (!checkReply<replySize>(waitTime, logMessage))
            return false;

        qCInfo(viscaLog()).noquote() << "Command executed" << logMessage;
        return true;
    }

    // TODO write documentaion
    template<std::size_t replySize, std::size_t size, typename TFuncRet>
    TFuncRet inquireCommand(const std::array <uint8_t, size> &&data,
                            TFuncRet (*processReplyFunc)(std::array <uint8_t, replySize>) = &checkMessageBytes<replySize>,
                            int waitTime = SHORT_WAIT_TIME_MS)
    {
        m_uart.sendMessage(m_camAddr, data);

        std::array <uint8_t, replySize> reply{};

        if (!m_uart.receiveMessage(reply, waitTime))
            qCWarning(viscaLog()) << "Failed to inquire";

        return processReplyFunc(reply);
    }

private:
    enum Result { SHORT, ERROR, ACKED, EXECUTED, UNKNOWN };

    UartCommunication m_uart;
    uint8_t m_camAddr;

    static const int INIT_TRIES_COUNT = 10;
    static const int DEFAULT_USLEEP_WAIT = 50000;

    static const int SHORT_WAIT_TIME_MS = 400; // TODO mby remake to BASE_WAIT_TIME
    static const int LONG_WAIT_TIME_MS = 600;

    enum addr : uint8_t {BROADCAST = 0x88, CAM_BASE = 0x80};

    bool setAddress();

    bool clearIF();

    template<std::size_t replySize>
    bool checkReply(int waitTime, QString &logMessage)
    {
        std::array <uint8_t, replySize> reply{};

        if (!m_uart.receiveMessage(reply, waitTime))
        {
            qCInfo(viscaLog()).noquote() << "Didn't recieve reply" << logMessage;
            return false;
        }

        Result res = checkMessageBytes(reply);

        // ERROR is 4B long, so I Have to throw away one byte later
        if (res != ERROR && reply[replySize - 1] != 0xFF)
        {
            qCWarning(viscaLog()) << "Messages out of sync! Throwing away buffer.";
            m_uart.ClearReplies();
            return false;
        }

        switch(res)
        {
            case SHORT:
                qCWarning(viscaLog()).noquote() << "Response is too short" << logMessage;
                return false;

            case ERROR:
            {
                qCWarning(viscaLog()).noquote() << "Error" << logMessage;
                std::array<uint8_t, 1> resp = {};
                m_uart.receiveMessage(resp, 400);
                return false;
            }

            case ACKED:
                qCInfo(viscaLog()).noquote() << "Command acknowledged" << logMessage;
                if (!m_uart.receiveMessage(reply, waitTime))
                {
                    qCInfo(viscaLog()).noquote() << "Didn't recieve command executed message" << logMessage;
                    return false;
                }
                break;

            case EXECUTED:
                break;

            case Visca::UNKNOWN:
                qCWarning(viscaLog()).noquote() << "Unkown response" << logMessage;
                return false;
        }

        return true;
    }

    template<std::size_t size = 3>
    static Result checkMessageBytes(std::array <uint8_t, size> &reply)
    {
        if (size <= 2)
        {
            qCWarning(viscaLog()) << "Reply is too short.";
            return SHORT;
        }

        if ((reply[1] & 0xF0) == 0x60)
        {
            printReplyError((err) reply[2]);
            return ERROR;
        }

        if (reply[1] == 0x41)
            return ACKED;

        if (reply[1] == 0x51)
            return EXECUTED;

        return UNKNOWN;
    }

    enum err : uint8_t {LENGTH = 0x01, SYNTAX = 0x02, BUFULL = 0x03, CANCEL = 0x04, SOCKET = 0x05, EXECUT = 0x41};

    ///! \brief used as complemenatry function for checkReply
    static void printReplyError(err code);
};

#endif // VISCA_H
