#ifndef VISCA_H
#define VISCA_H

#include "library/visca/uartCommunication.h"
#include "global/logCategories.h"

/*!
 * \brief Class with basic VISCA commands - facade on UartCommunication class
 */
class Visca
{
public:
    Visca(const char* device_path);

    bool executeCommand();
    bool executeCommandUnchecked();

    bool zoomTeleStandard();
    bool zoomWideStandard();

private:
    bool checkReply(uint8_t* reply, uint8_t size);

    bool setAddress();
    bool clearIF();

    UartCommunication m_uart;

    uint8_t m_camAddress;

    static const int INIT_TRIES_COUNT = 10;
    static const int DEFAULT_USLEEP_WAIT = 50000;

    struct addr {
        static const uint8_t BROADCAST = 0x88;
        static const uint8_t CAM_BASE = 0x80;
    };

    struct err {
        static const uint8_t LENGTH = 0x01;
        static const uint8_t SYNTAX = 0x02;
        static const uint8_t BUFULL = 0x03;
        static const uint8_t CANCEL = 0x04;
        static const uint8_t SOCKET = 0x05;
        static const uint8_t EXECUT = 0x06;
    };

    static const uint8_t TERMINATOR = 0xFF;


};

#endif // VISCA_H
