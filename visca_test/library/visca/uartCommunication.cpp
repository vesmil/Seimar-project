#include "uartCommunication.h"

#include <cstdint>
#include <termios.h>
#include <fcntl.h>
#include <stdexcept>
#include <string.h>
#include <sys/ioctl.h>
#include <QDebug>

UartCommunication::UartCommunication(const char* device_path)
{
    m_descriptor = open(device_path, O_RDWR | O_NOCTTY | O_NDELAY);

    if (m_descriptor == -1)
    {
        qCWarning(viscaWarning()) << __PRETTY_FUNCTION__ << ": Error while openning" << device_path << "for UART communication.";
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
}

bool UartCommunication::sendMessage(uint8_t *message, int size)
{
    int sent_size = write(m_descriptor, message, size);
    if (sent_size != size)
    {
        if (sent_size == -1)
            qCWarning(viscaWarning()) << __PRETTY_FUNCTION__ << ": Error, UART sending error!";
        else
            qCWarning(viscaWarning()) << __PRETTY_FUNCTION__ << ": Error, sent less bytes than requested!";

        return false;
    }

    return true;
}

bool UartCommunication::receiveMessage(uint8_t *data, int size, int waitMs)
{
    if (LoadMessageToPrivateBuffer(size, waitMs))
    {
        memcpy(&m_buffer, data, size);
        return true;
    }

    return false;
}

bool UartCommunication::LoadMessageToPrivateBuffer(int size, int waitMs)
{
    if (m_descriptor == -1)
    {
        qCWarning(viscaWarning()) << __PRETTY_FUNCTION__ << ": Error, port is closed";
        return -1;
    }

    const int checkLoops = waitMs / 10 + 1;
    for (int i = 0; i < checkLoops; ++i)
    {
        if (ioctl(m_descriptor, FIONREAD) >= size)
            break;

        usleep(USECONDS_PER_CHECK);
    }

    if (read(m_descriptor, m_buffer, MAX_BUFFER_SIZE) < 3)
    {
        qCWarning(viscaWarning()) << __PRETTY_FUNCTION__ << ": Error, less than 3 bytes recieved!";
        return false;
    }

    return true;
}
