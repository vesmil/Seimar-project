#include "visca.h"

#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdexcept>
#include <string.h>
#include <sys/ioctl.h>
#include <QDebug>

#include "global/viscaConfig.h"
#include "global/logCategories.h"

Visca::Visca()
{
    m_descriptor = open(m_device, O_RDWR | O_NOCTTY | O_NDELAY);

    if (m_descriptor == -1) {
        qCWarning(viscaWarning()) << "Visca::Visca() Error while openning " << m_device << " for UART communication.";
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

    for (int i = 0; i < glb::visca::numOfTries; i++) {
        if (setAddress() && clearIF())
            return;

        usleep(100000);
    }

    qCWarning(viscaWarning()) << "Visca::Visca(): Error while initializing UART communication.";
}

bool Visca::setAddress()
{
    if (!sendMessage(0x88, 0x30, 0x01, buffer, 0)) {
        return false;
    }

    uint8_t addr, socket;

    if (!receiveMessage(addr, socket, buffer, 1)) {
        // ...
        return false;
    }

    qCInfo(viscaInfo()) << "ViscaSetting::setAddress(): Returned device address " << addr - 1;
    return true;
}

bool Visca::clearIF()
{
    return true;
}

bool Visca::sendBytes(uint8_t *buffer, int size)
{
    if (m_descriptor == -1) {
        qCWarning(viscaWarning()) << "Visca::sendBytes(): Error, UART port is closed";
        return -1;
    }

    int sent_size = write(m_descriptor, buffer, size);

    qCWarning(viscaInfo()) << "Sent" << sent_size << "bytes";

    if (sent_size < 0) {
        qCWarning(viscaWarning()) << "Visca::sendBytes(): Error, UART sending error!";
        return -2;
    }

    return sent_size == size;
}

bool Visca::sendMessage(uint8_t addr, uint8_t comm, uint8_t cat, uint8_t *data, int size)
{
    unsigned total = 4 + size;
    uint8_t message[total];

    message[0] = addr;
    message[1] = comm;
    message[2] = cat;

    memcpy(&message[3], data, size);
    message[total-1] = 0xFF;

    return sendBytes(message, total);
}

int Visca::receiveBytes(uint8_t *buffer)
{
    if (m_descriptor == -1) {
        qCWarning(viscaWarning()) << "Visca::recieveBytes(): Error, UART port is closed";
        return -1;
    }

    int recieved_size = read(m_descriptor, buffer, MAX_RX_BUFFER);

    qCWarning(viscaInfo()) << recieved_size;

    if (recieved_size <= 3) {
        qCWarning(viscaWarning()) << "Visca::recieveBytes(): Error, UART recieving error!";
        return recieved_size;
    }

    return recieved_size;
}

bool Visca::receiveMessage(uint8_t &addr, uint8_t &socket, uint8_t *data, int size)
{
    int recieved_size = receiveBytes(buffer);

    if (recieved_size < 3)
        return false;

    addr = buffer[0];
    socket = buffer[1];

    memcpy(&buffer[2], data, recieved_size - 3);

    return recieved_size - 3 == size;
}
