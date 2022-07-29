#ifndef VISCA_H
#define VISCA_H

#include <cstdint>

class Visca
{
public:
    Visca();

private:
    bool setAddress();
    bool clearIF();

    bool sendBytes(uint8_t *buffer, int size);
    bool sendMessage(uint8_t addr, uint8_t comm, uint8_t cat, uint8_t *data, int size);

    int receiveBytes(uint8_t *buffer);
    bool receiveMessage(uint8_t &addr, uint8_t &socket, uint8_t *data, int size);

    int m_descriptor;
    const char* m_device = "/dev/ttymxc4";

    static const unsigned MAX_RX_BUFFER = 512;
    uint8_t buffer[MAX_RX_BUFFER];

    static const uint8_t ERR_LENGTH = 0x01;
    static const uint8_t ERR_SYNTAX = 0x02;
    static const uint8_t ERR_BUFULL = 0x03;
    static const uint8_t ERR_CANCEL = 0x04;
    static const uint8_t ERR_SOCKET = 0x05;
    static const uint8_t ERR_EXECUT = 0x06;
};

#endif // VISCA_H
