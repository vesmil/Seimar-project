#ifndef VISCA_H
#define VISCA_H

#include "uartcommunication.h"
#include "global/logcategories.h"

/*!
 * \brief Class with basic VISCA commands - facade on UartCommunication class
 */
class Visca {
public:
    /*!
     * \brief Initilize all necessary components for VISCA communication
     * \param portName - name of serial port (path to device)
     */
    explicit Visca(const char *device_path);

    /*!
     * \brief Send VISCA command to camera
     * @tparam TReplySize - expected size of reply, usually 3 bytes (default value)
     * @tparam size - size of command (usually auto deduced)
     * @param data - command to send (best to generate them from ViscaCommands.h)
     * @param waitTime - time to wait for reply (in milliseconds)
     * @param logMessage - name of executed command for logging purposes
     * @return
     */
    template<std::size_t TReplySize = 3, std::size_t TSize>
    bool executeCommand(const std::array <uint8_t, TSize> &&data,
                        int waitTime = BASE_WAIT_TIME_MS,
                        QString &&logMessage = QString{})
    {
        if (logMessage.length() != 0)
            logMessage = "(" + logMessage + ")";

        if (!m_uart.sendMessage(m_camAddr, data))
        {
            qCInfo(viscaLog()).noquote() << "Failed sending" << logMessage;
            return false;
        }

        if (!checkReply<TReplySize>(waitTime, logMessage))
            return false;

        qCInfo(viscaLog()).noquote() << "Command executed" << logMessage;

        return true;
    }

    /*!
     * \brief Send VISCA inquiry command (request camera to send some information)
     * @tparam TReplySize - expected TSize of reply - auto deduced
     * @tparam TSize - TSize of command - auto deduced
     * @tparam TFuncRet - return type of processing function - auto deduced
     * @param data - command to send (best to generate them from ViscaCommands.h)
     * @param processReplyFunc - function to process reply
     * @param waitTime - time to wait for reply (in milliseconds)
     * @return what processing function returns
     * @example inquireCommand(ViscaCommands::Zoom::getValue(), ViscaCommands::Zoom::valueFromReply);
     */
    template<std::size_t TReplySize, std::size_t TSize, typename TFuncRet>
    TFuncRet inquireCommand(const std::array <uint8_t, TSize> &&data,
                            TFuncRet (*processReplyFunc)(std::array <uint8_t, TReplySize>) = &checkMessageBytes < TReplySize >,
                            int waitTime = BASE_WAIT_TIME_MS)
    {
        m_uart.sendMessage(m_camAddr, data);

        std::array <uint8_t, TReplySize> reply{};

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

    static const int BASE_WAIT_TIME_MS = 200;

    enum addr : uint8_t {BROADCAST = 0x88, CAM_BASE = 0x80};

    /*!
     * \brief Initialize camera address
     */
    bool setAddress();

    /*!
     * \brief Check reply from camera - if acknowledged, executed, error...
     * @tparam TReplySize - expected size of reply, usually 3 bytes (default value)
     * @param waitTime - time to wait for reply (in milliseconds)
     * @param logMessage - name of executed command for logging purposes
     * @return true if reply is valid, false otherwise
     */
    template<std::size_t TReplySize>
    bool checkReply(int waitTime, QString &logMessage)
    {
        std::array <uint8_t, TReplySize> reply{};

        if (!m_uart.receiveMessage(reply, waitTime))
        {
            qCInfo(viscaLog()).noquote() << "Didn't recieve reply" << logMessage;
            return false;
        }

        Result res = checkMessageBytes(reply);

        // Check correct terminating symbol (ERROR doesn't have default length)
        if (res != ERROR && reply[TReplySize - 1] != 0xFF)
        {
            qCWarning(viscaLog()) << "Messages out of sync! Throwing away unread bytes.";
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
                // Throwing away one byte (ERROR is one byte longer)
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
            case Visca::UNKNOWN:
                qCWarning(viscaLog()).noquote() << "Unkown response" << logMessage;
                return false;
            case EXECUTED:
                break;
        }

        return true;
    }

    /*!
     * \brief Check what type of reply is it - short, error, acked, executed, unknown
     * @tparam TReplySize - expected size of reply, usually 3 bytes (default value)
     * @param reply - array of bytes to check
     * @return result of checking
     */
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

    /*!
     * \brief Print error message from camera based on error code
     */
    static void printReplyError(err code);
};

#endif // VISCA_H
