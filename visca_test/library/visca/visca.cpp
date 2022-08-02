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

        qCInfo(viscaInfo()) <<  __PRETTY_FUNCTION__ << ": Failed to initialize - attempt:" << i + 1 << "out of" << INIT_TRIES_COUNT;
        usleep(DEFAULT_USLEEP_WAIT);
    }

    qCWarning(viscaWarning()) << __PRETTY_FUNCTION__ << ": Error while initializing UART communication!";
}

bool Visca::setAddress()
{
    uint8_t reply[4];
    // if (!m_uart.sendMessageArr(ViscaComm<addr::BROADCAST>::Init::ADDRESS_SET, 4) || !m_uart.receiveMessage(reply, 4, 100))

    if (!m_uart.sendMessage(addr::BROADCAST, 0x88, 0x30, 0x01, TERMINATOR) || !m_uart.receiveMessage(reply, 4, 200))
    {
        qCInfo(viscaWarning()) << __PRETTY_FUNCTION__ << ": failed to set address.";
        return false;
    }

    m_camAddress = reply[2] - 1;

    qCInfo(viscaInfo()) << __PRETTY_FUNCTION__ << ": Address set succesfull, returned device address:" << hex << reply[2] - 1;
    return true;
}

bool Visca::clearIF()
{
    uint8_t reply[3];
    if (!m_uart.sendMessage(addr::CAM_BASE + m_camAddress, 0x01, 0x00, 0x01, TERMINATOR) || !m_uart.receiveMessage(reply, 3, 300))
    {
        qCInfo(viscaWarning()) << __PRETTY_FUNCTION__ << ": failed to clear command buffer.";
        return false;
    }

    qCInfo(viscaInfo()) << __PRETTY_FUNCTION__ << ": Command buffer cleared";
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

    qCInfo(viscaInfo()) << __PRETTY_FUNCTION__ << ": executing.";
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

    qCInfo(viscaInfo()) << __PRETTY_FUNCTION__ << ": executing.";
    return true;
}


bool Visca::checkReply(uint8_t* reply, uint8_t size)
{
    if (size < 2 )
    {
        qCWarning(viscaWarning()) << __PRETTY_FUNCTION__ << ": reply is too short.";
        return false;
    }

    if ((reply[1] & 0xF0) == 0x60)
    {
        if (size == 2 )
        {
            qCWarning(viscaWarning()) << __PRETTY_FUNCTION__ << ": reply doesn't provide any description.";
        }
        else
        {
            switch (reply[2])
            {
                case err::LENGTH:
                    qCWarning(viscaWarning()) << __PRETTY_FUNCTION__ << ": Message length error";
                    break;
                case err::SYNTAX:
                    qCWarning(viscaWarning()) << __PRETTY_FUNCTION__ << ": Syntax Error";
                    break;
                case err::BUFULL:
                    qCWarning(viscaWarning()) << __PRETTY_FUNCTION__ << ": Command buffer full";
                    break;
                case err::CANCEL:
                    qCWarning(viscaWarning()) << __PRETTY_FUNCTION__ << ": Command canceled";
                    break;
                case err::SOCKET:
                    qCWarning(viscaWarning()) << __PRETTY_FUNCTION__ << ": No socket (to be canceled)";
                    break;
                case err::EXECUT:
                    qCWarning(viscaWarning())<< __PRETTY_FUNCTION__ << ": Command not executable";
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

    if (!m_uart.loadMessageToBuffer(0, 200))
        return false;

    qCInfo(viscaInfo()) << __PRETTY_FUNCTION__ << ": Zooming";
    return true;
}

bool Visca::zoomWideStandard(void)
{
    if (!m_uart.sendMessage(addr::CAM_BASE + m_camAddress, 0x01, 0x04, 0x07, 0x03, TERMINATOR))
        return false;

    if (!m_uart.loadMessageToBuffer(0, 200))
        return false;

    qCInfo(viscaInfo()) << __PRETTY_FUNCTION__ << ": Unzooming";
    return true;
}

