#include "uartCommunication.h"

#include <termios.h>
#include <fcntl.h>

UartCommunication::UartCommunication(const char* device_path)
{
    m_descriptor = open(device_path, O_RDWR | O_NOCTTY | O_NDELAY);

    if (m_descriptor == -1)
    {
        qCWarning(viscaLog()) << "Error while openning" << device_path << "for UART communication.";
        return;
    }

    struct termios options{};

    tcgetattr(m_descriptor, &options);
    options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(m_descriptor, TCIFLUSH);
    tcsetattr(m_descriptor, TCSANOW, &options);

    qCInfo(viscaLog()) << "UART communication initalized on port" << m_descriptor;
}

UartCommunication::~UartCommunication()
{
    close(m_descriptor);
}
