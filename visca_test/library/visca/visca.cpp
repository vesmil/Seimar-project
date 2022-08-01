#include "visca.h"
#include "global/logCategories.h"

Visca::Visca(const char* device_path) : m_visca_comm(device_path)
{
}

// TODO create template for commands
bool Visca::zoomTeleStandard(void)
{
    uint8_t data[] = {0x07, 0x02};

    if (!m_visca_comm.sendMessage(0x80 + 1, 0x01, 0x04, data, 2))
        return false;

    if (!m_visca_comm.receiveMessageData(nullptr, 0, 200))
        return false;

    qCInfo(viscaInfo()) << "ViscaCommunication::zoomTeleStandard(): Zooming";
    return true;
}

bool Visca::zoomWideStandard(void)
{
    uint8_t data[] = {0x07, 0x03};

    if (!m_visca_comm.sendMessage(0x80 + 1, 0x01, 0x04, data, 2))
        return false;

    if (!m_visca_comm.receiveMessageData(nullptr, 0, 200))
        return false;

    qCInfo(viscaInfo()) << "ViscaCommunication::zoomWideStandard(): Unzooming";
    return true;
}
