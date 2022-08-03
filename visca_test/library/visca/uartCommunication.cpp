#include "uartCommunication.h"

#include <termios.h>
#include <fcntl.h>
#include <stdexcept>
#include <unistd.h>
#include <sys/ioctl.h>

#include "global/logCategories.h"

UartCommunication::UartCommunication(const char* device_path)
{
    m_descriptor = open(device_path, O_RDWR | O_NOCTTY | O_NDELAY);

    if (m_descriptor == -1)
    {
        qCWarning(viscaWarning()) << "Error while openning" << device_path << "for UART communication.";
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

    qCWarning(viscaInfo()) << "UART communication initalized on port" << m_descriptor;
}

UartCommunication::~UartCommunication()
{
    close(m_descriptor);
}

bool UartCommunication::sendMessageArr(uint8_t *message, const uint8_t size)
{
    if (m_descriptor == -1)
    {
        qCWarning(viscaWarning()) << "Error, port is closed!";
        return false;
    }

    int sent_size = write(m_descriptor, message, size);
    if (sent_size != size)
    {
        if (sent_size == -1)
            qCWarning(viscaWarning()) << "Error, UART sending error!";
        else
            qCWarning(viscaWarning()) << "Error, sent less bytes than requested!";

        return false;
    }

    return true;
}

bool UartCommunication::receiveMessage(uint8_t *data, int size, int waitMs)
{
    if (m_descriptor == -1)
    {
        qCWarning(viscaWarning()) << "Error, port is closed";
        return -1;
    }

    const int checkLoops = waitMs / 10 + 1;
    for (int i = 0; i < checkLoops; ++i)
    {
        if (ioctl(m_descriptor, FIONREAD) >= size)
            break;

        usleep(USECONDS_PER_CHECK);
    }

    int read_count = read(m_descriptor, data, size);

    if (read_count != size && read_count < 3)
    {
        qCWarning(viscaWarning()) << "Error, less than 3 bytes recieved!";
        return false;
    }

    return true;
}

bool UartCommunication::loadMessageToBuffer(int size, int waitMs)
{
    return receiveMessage(m_buffer, size, waitMs);
}
