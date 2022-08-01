#ifndef VISCA_H
#define VISCA_H

#include "library/visca/uartCommunication.h"

/*!
 * \brief Class with basic VISCA commands - facade on UartCommunication class
 */
class Visca
{
public:
    Visca(const char* device_path);

    bool zoomTeleStandard();
    bool zoomWideStandard();

private:
    template<uint8_t ... data>
    bool generalCommand(){
        if (!m_visca_comm.sendMessage<data...>()) {
            // ...
            return false;
        }

        if(!m_visca_comm.LoadMessageToPrivateBuffer(0, 10))
        {
            // ...
            return false;
        }

        qCInfo(viscaInfo()) << __PRETTY_FUNCTION__ << ": ...command executed";
        return true;
    }

    bool setAddress();
    bool clearIF();

    UartCommunication m_visca_comm;

    static const int INIT_TRIES_COUNT = 10;
    static const int DEFAULT_USLEEP_WAIT = 50000;
};

#endif // VISCA_H
