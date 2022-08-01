#include "viscaCommunication.h"

#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdexcept>
#include <string.h>
#include <sys/ioctl.h>
#include <QDebug>

#include "global/viscaConfig.h"
#include "global/logCategories.h"

ViscaCommunication::ViscaCommunication(const char* device_path) : m_device(device_path)
{
    m_descriptor = open(m_device, O_RDWR | O_NOCTTY | O_NDELAY);

    if (m_descriptor == -1) {
        qCWarning(viscaWarning()) << "Visca::Visca() Error while openning" << m_device << "for UART communication.";
        return;
    }

    struct termios options;

    tcgetattr(m_descriptor, &options);
    options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(m_descriptor, TCIFLUSH);
    tcsetattr(m_descriptor, TCSANOW, &options);

    for (int i = 0; i < glb::visca::INIT_LIMIT_COUNT; i++) {

        if (setAddress() && clearIF())
            return;

        usleep(100000);
    }

    qCWarning(viscaWarning()) << "Visca::Visca(): Error while initializing UART communication";
}

bool ViscaCommunication::setAddress()
{
    if (!sendMessage(0x88, 0x30, 0x01, m_buffer, 0)) {
        qCInfo(viscaWarning()) << "ViscaSetting::setAddress(): failed to send message";
        return false;
    }

    usleep(100000);

    uint8_t addr = 0;
    uint8_t socket;

    if (!receiveMessage(addr, socket, m_buffer, 1)) {
        qCInfo(viscaWarning()) << "ViscaSetting::setAddress(): failed to recieve message!";
        return false;
    }

    qCInfo(viscaInfo()) << "ViscaSetting::setAddress(): Returned device address" << addr;
    return true;
}

bool ViscaCommunication::clearIF()
{
    uint8_t data[] = {0x01};

    if (!sendMessage(0x88, 0x01, 0x00, data, 1)) {
        return false;
    }

    uint8_t addr, soc;
    uint8_t dataRet[2];

    if (!receiveMessage(addr, soc, dataRet, 2, 500)) {
        return false;
    }

    qCInfo(viscaInfo()) << "ViscaSetting::clearIF(): Command buffer cleared";
    return true;
}

bool ViscaCommunication::sendBytes(uint8_t *buffer, int size)
{
    if (m_descriptor == -1) {
        qCWarning(viscaWarning()) << "Visca::sendBytes(): Error, UART port is closed!";
        return false;
    }

    int sent_size = write(m_descriptor, buffer, size);

    if (sent_size < 0) {
        qCWarning(viscaWarning()) << "Visca::sendBytes(): Error, UART sending error!";
        return false;
    }

    if (sent_size != size) {
        qCWarning(viscaWarning()) << "Visca::sendBytes(): Error, sent less bytes than requested!";
        return false;
    }

    return true;
}

bool ViscaCommunication::sendMessage(uint8_t addr, uint8_t comm, uint8_t cat, uint8_t *data, int size)
{
    unsigned total = 4 + size;
    uint8_t message[total];

    message[0] = addr;
    message[1] = comm;
    message[2] = cat;

    memcpy(&message[3], data, size);

    message[total-1] = 0xFF; // termination symbol

    return sendBytes(message, total);
}

int ViscaCommunication::receiveBytes(uint8_t *buffer)
{
    if (m_descriptor == -1) {
        qCWarning(viscaWarning()) << "Visca::recieveBytes(): Error, UART port is closed";
        return -1;
    }

    return read(m_descriptor, buffer, MAX_RX_BUFFER);
}

// TODO remake variadic
bool ViscaCommunication::receiveMessage(uint8_t &addr, uint8_t &socket, uint8_t *data, int size, int waitMs)
{
    const int checkLoops = waitMs / 10 + 1;

    for (int i = 0; i < checkLoops; ++i) {
        if (ioctl(m_descriptor, FIONREAD) >= size)
            break;

        usleep(10000);
    }

    int recieved_size = receiveBytes(m_buffer);

    if (recieved_size < 3) {
        qCWarning(viscaWarning()) << "Visca::recieveBytes(): Error, less than 3 bytes recieved!";
        return recieved_size;
    }

    addr = m_buffer[0];
    socket = m_buffer[1];

    if (data) // Could be a null pointer
        memcpy(&m_buffer[2], data, recieved_size - 3);

    return recieved_size - 3 == size;
}

// TODO remake variadic
bool ViscaCommunication::receiveMessageData(uint8_t *data, int size, int waitMs)
{
    uint8_t addr, socket;
    return receiveMessage(addr,socket, data, size, waitMs);
}
