#include "visca.h"

#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdexcept>
#include <string.h>
#include <sys/ioctl.h>

#include <QDebug>

Visca::Visca()
{
    int descriptor = open("/dev/video0", O_RDWR | O_NOCTTY | O_NDELAY); //Open in non blocking read/write mode

    if (descriptor == -1) {
        throw std::runtime_error("Couldn't connect to camera");
    }

    struct termios options;

    tcgetattr(descriptor, &options);
    options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(descriptor, TCIFLUSH);
    tcsetattr(descriptor, TCSANOW, &options);

    // Set Address

    // Clear...
}
