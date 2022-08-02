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

    bool zoomTeleStandard();
    bool zoomWideStandard();

private:
    bool setAddress();
    bool clearIF();

    UartCommunication m_visca_comm;

    static const int INIT_TRIES_COUNT = 10;
    static const int DEFAULT_USLEEP_WAIT = 50000;
};

#endif // VISCA_H
