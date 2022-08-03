#include "visca.h"
#include <unistd.h>

#include "global/logCategories.h"
#include "viscaCommands.h"

Visca::Visca(const char* device_path) : m_uart(device_path)
{
    for (int i = 0; i < INIT_TRIES_COUNT; i++)
    {
        if (setAddress() && clearIF())
            return;

        qCInfo(viscaInfo()) << "Failed to initialize - attempt:" << i + 1 << "out of" << INIT_TRIES_COUNT;
        usleep(DEFAULT_USLEEP_WAIT);
    }

    qCWarning(viscaWarning()) << "Error while initializing UART communication!";
}

bool Visca::setAddress()
{
    uint8_t reply[4];
    if (!m_uart.sendMessage(0x88, 0x30, 0x01,  0xFF) || !m_uart.receiveMessage(reply, 4, SHORT_WAIT_TIME))
    {
        qCInfo(viscaWarning()) << "Failed to set address.";
        return false;
    }

    m_camAddress = reply[2] - 1;

    qCInfo(viscaInfo()) << "Address set succesfull, returned device address:" << hex << reply[2] - 1;
    return true;
}

bool Visca::clearIF()
{
    uint8_t reply[3];

    ViscaCommands::Init::IF_CLEAR[0] = addr::CAM_BASE + m_camAddress;
    if (!m_uart.sendMessageArr(ViscaCommands::Init::IF_CLEAR,5) || !m_uart.receiveMessage(reply, 3, LONG_WAIT_TIME))
    {
        qCInfo(viscaWarning()) << "Failed to clear command buffer.";
        return false;
    }

    qCInfo(viscaInfo()) << "Command buffer cleared";
    return true;
}

bool Visca::executeCommand()
{
    if (!m_uart.sendMessage(addr::CAM_BASE + m_camAddress, 0x01, 0x04, 0x07, 0x02, TERMINATOR))
        return false;

    uint8_t reply[4];
    if (!m_uart.receiveMessage(reply, 4, 100))
        return false;

    if (!checkReply(reply, 4))
        return false;

    qCInfo(viscaInfo()) << "Executing.";
    return true;
}

bool Visca::executeCommandUnchecked()
{
    if (!m_uart.sendMessage(addr::CAM_BASE + m_camAddress, 0x01, 0x04, 0x07, 0x02, TERMINATOR))
        return false;

    uint8_t reply[4];
    if (!m_uart.receiveMessage(reply, 4, 100))
        return false;

    if (!checkReply(reply, 4))
        return false;

    qCInfo(viscaInfo()) << "Executing.";
    return true;
}

bool Visca::checkReply(uint8_t* reply, uint8_t size)
{
    if (size < 2 )
    {
        qCWarning(viscaWarning()) << "Reply is too short.";
        return false;
    }

    if ((reply[1] & 0xF0) == 0x60)
    {
        if (size == 2 )
        {
            qCWarning(viscaWarning()) << "Reply doesn't provide any description.";
        }
        else
        {
            switch (reply[2])
            {
                case err::LENGTH:
                    qCWarning(viscaWarning()) << "Message length error";
                    break;
                case err::SYNTAX:
                    qCWarning(viscaWarning()) << "Syntax Error";
                    break;
                case err::BUFULL:
                    qCWarning(viscaWarning()) << "Command buffer full";
                    break;
                case err::CANCEL:
                    qCWarning(viscaWarning()) << "Command canceled";
                    break;
                case err::SOCKET:
                    qCWarning(viscaWarning()) << "No socket (to be canceled)";
                    break;
                case err::EXECUT:
                    qCWarning(viscaWarning()) << "Command not executable";
                    break;
            }
        }
        return false;
    }

    return true;
}


// TODO remove
bool Visca::zoomTeleStandard(void)
{
    if (!m_uart.sendMessage(addr::CAM_BASE + m_camAddress, 0x01, 0x04, 0x07, 0x02, TERMINATOR))
        return false;

    if (!m_uart.loadMessageToBuffer(3, 200))
        return false;

    qCInfo(viscaInfo()) << "Zooming";
    return true;
}

bool Visca::zoomWideStandard(void)
{
    if (!m_uart.sendMessage(addr::CAM_BASE + m_camAddress, 0x01, 0x04, 0x07, 0x03, TERMINATOR))
        return false;

    if (!m_uart.loadMessageToBuffer(3, 200))
        return false;

    qCInfo(viscaInfo()) << "Unzooming";
    return true;
}

