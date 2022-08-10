#include "visca.h"
#include <unistd.h>

#include "global/logCategories.h"
#include "viscaCommands.h"

Visca::Visca(const char *device_path) : m_uart(device_path) {
    for (int i = 0; i < INIT_TRIES_COUNT; i++) {
        if (!setAddress()) {
            qCWarning(viscaLog()) << "Failed to set address - init attempt:" << i + 1 << "out of" << INIT_TRIES_COUNT;
            continue;
        }

        if (executeCommand(ViscaCommands::Init::ifClear(), BASE_WAIT_TIME_MS * 2, "Clearing command buffer"))
            return;

        qCWarning(viscaLog()) << "Failed to clear command buffer - init attempt:" << i + 1 << "out of" << INIT_TRIES_COUNT;
        usleep(DEFAULT_USLEEP_WAIT);
    }

    qCWarning(viscaLog()) << "Error while initializing UART communication!";
}

bool Visca::setAddress() {
    std::array<uint8_t, 4> reply;
    if (!m_uart.sendMessage(addr::BROADCAST, ViscaCommands::Init::addressSet()) || !m_uart.receiveMessage(reply, BASE_WAIT_TIME_MS)) {
        qCWarning(viscaLog()) << "Failed to set address.";
        return false;
    }

    m_camAddr = reply[2] - 1 + addr::CAM_BASE;

    qCInfo(viscaLog()) << "Address set succesfull, returned device address:" << hex << reply[2] - 1;
    return true;
}

void Visca::printReplyError(err code) {
    switch (code) {
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
        default:
            qCWarning(viscaLog()) << "Unknown error";
            break;
    }
}
