#include "viscaCommunication.h"

#include <cstdint>
#include <termios.h>
#include <fcntl.h>
#include <stdexcept>
#include <string.h>
#include <sys/ioctl.h>
#include <QDebug>

#include "global/viscaConfig.h"

ViscaCommunication::ViscaCommunication(const char* device_path)
{
    m_descriptor = open(device_path, O_RDWR | O_NOCTTY | O_NDELAY);

    if (m_descriptor == -1)
    {
        qCWarning(viscaWarning()) << "Visca::Visca() Error while openning" << device_path << "for UART communication.";
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

    for (int i = 0; i < glb::visca::INIT_TRIES_COUNT; i++)
    {
        if (setAddress() && clearIF())
            return;

        qCInfo(viscaInfo()) << "ViscaCommunication::ViscaCommunication(): Failed to initialize - attempt:" << i << "out of" << glb::visca::INIT_TRIES_COUNT;
        usleep(glb::visca::DEF_USLEEP_T);
    }

    qCWarning(viscaWarning()) << "Visca::Visca(): Error while initializing UART communication!";
}

bool ViscaCommunication::sendMessage(uint8_t *message, int size)
{
    int sent_size = write(m_descriptor, message, size);

    if (sent_size != size)
    {
        if (sent_size == -1)
            qCWarning(viscaWarning()) << "Visca::sendBytes(): Error, UART sending error!";
        else
            qCWarning(viscaWarning()) << "Visca::sendBytes(): Error, sent less bytes than requested!";
        return false;
    }

    return true;
}

bool ViscaCommunication::setAddress()
{
    uint8_t addr[1];
    if (!sendMessage<0x88, 0x30, 0x01>() || !receiveMessage(addr, 1, 100))
    {
        qCInfo(viscaWarning()) << "ViscaSetting::setAddress(): failed to set address.";
        return false;
    }

    qCInfo(viscaInfo()) << "ViscaSetting::setAddress(): Returned device address" << addr[0];
    return true;
}

bool ViscaCommunication::clearIF()
{
    if (!sendMessage<0x88, 0x01, 0x00, 0x01>() || !LoadMessageToPrivateBuffer(2, 500))
    {
        qCInfo(viscaWarning()) << "ViscaSetting::setAddress(): failed to clear command buffer.";
        return false;
    }

    qCInfo(viscaInfo()) << "ViscaSetting::clearIF(): Command buffer cleared";
    return true;
}

bool ViscaCommunication::receiveMessage(uint8_t *data, int size, int waitMs)
{
    if (LoadMessageToPrivateBuffer(size, waitMs))
    {
        memcpy(&m_buffer, data, size);
        return true;
    }

    return false;
}

bool ViscaCommunication::LoadMessageToPrivateBuffer(int size, int waitMs)
{
    if (m_descriptor == -1)
    {
        qCWarning(viscaWarning()) << "Visca::LoadMessageToBuffer(): Error, UART port is closed";
        return -1;
    }

    const int checkLoops = waitMs / 10 + 1;
    for (int i = 0; i < checkLoops; ++i)
    {
        if (ioctl(m_descriptor, FIONREAD) >= size)
            break;

        usleep(glb::visca::DEF_USLEEP_T);
    }

    if (read(m_descriptor, m_buffer, MAX_BUFFER_SIZE) < 3)
    {
        qCWarning(viscaWarning()) << "Visca::LoadMessageToBuffer(): Error, less than 3 bytes recieved!";
        return false;
    }

    return true;
}
