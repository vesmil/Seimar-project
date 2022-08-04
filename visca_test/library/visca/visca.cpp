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

        qCWarning(viscaLog()) << "Failed to initialize - attempt:" << i + 1 << "out of" << INIT_TRIES_COUNT;
        usleep(DEFAULT_USLEEP_WAIT);
    }

    qCWarning(viscaLog()) << "Error while initializing UART communication!";
}

bool Visca::setAddress()
{
    std::array<uint8_t, 4> reply;
    if (!m_uart.sendMessageArr(addr::BROADCAST, ViscaControlCommands::Init::AddressSet()) || !m_uart.receiveMessage(reply, SHORT_WAIT_TIME_MS))
    {
        qCWarning(viscaLog()) << "Failed to set address.";
        return false;
    }

    m_camAddr = reply[2] - 1 + addr::CAM_BASE;

    qCInfo(viscaLog()) << "Address set succesfull, returned device address:" << hex << reply[2] - 1;
    return true;
}

bool Visca::clearIF()
{
    return executeCommand(ViscaControlCommands::Init::IfClear(), LONG_WAIT_TIME_MS, "Clearing command buffer");
}
