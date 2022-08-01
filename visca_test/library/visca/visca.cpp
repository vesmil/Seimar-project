#include "visca.h"
#include "global/logCategories.h"

Visca::Visca(const char* device_path) : m_visca_comm(device_path)
{
    for (int i = 0; i < INIT_TRIES_COUNT; i++)
    {
        if (setAddress() && clearIF())
            return;

        qCInfo(viscaInfo()) <<  __PRETTY_FUNCTION__ << ": Failed to initialize - attempt:" << i << "out of" << INIT_TRIES_COUNT;
        usleep(DEFAULT_USLEEP_WAIT);
    }

    qCWarning(viscaWarning()) << __PRETTY_FUNCTION__ << ": Error while initializing UART communication!";
}

// TODO create template for general commands to minimize copypasting
bool Visca::setAddress()
{
    uint8_t reply[3];
    if (!m_visca_comm.sendMessage<0x88, 0x30, 0x01>() || !m_visca_comm.receiveMessage(reply, 3, 100))
    {
        qCInfo(viscaWarning()) << __PRETTY_FUNCTION__ << ": failed to set address.";
        return false;
    }

    qCInfo(viscaInfo()) << __PRETTY_FUNCTION__ << ": Returned device address" << reply[0] << reply[1] << reply[2];
    return true;
}

bool Visca::clearIF()
{
    if (!m_visca_comm.sendMessage<0x81, 0x01, 0x00, 0x01>() || !m_visca_comm.LoadMessageToPrivateBuffer(2, 500))
    {
        qCInfo(viscaWarning()) << __PRETTY_FUNCTION__ << ": failed to clear command buffer.";
        return false;
    }

    qCInfo(viscaInfo()) << __PRETTY_FUNCTION__ << ": Command buffer cleared";
    return true;
}

bool Visca::zoomTeleStandard(void)
{
    if (!m_visca_comm.sendMessage<0x80 + 1, 0x01, 0x04, 0x07, 0x02>())
        return false;

    if (!m_visca_comm.LoadMessageToPrivateBuffer(0, 200))
        return false;

    qCInfo(viscaInfo()) << __PRETTY_FUNCTION__ << ": Zooming";
    return true;
}

bool Visca::zoomWideStandard(void)
{
    if (!m_visca_comm.sendMessage<0x80 + 1, 0x01, 0x04, 0x07, 0x03>())
        return false;

    if (!m_visca_comm.LoadMessageToPrivateBuffer(0, 200))
        return false;

    qCInfo(viscaInfo()) << __PRETTY_FUNCTION__ << ": Unzooming";
    return true;
}

