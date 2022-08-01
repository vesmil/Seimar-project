#ifndef VISCA_H
#define VISCA_H

#include "library/visca/viscaCommunication.h"

class Visca
{
public:
    Visca(const char* device_path);

    bool zoomTeleStandard();
    bool zoomWideStandard();

private:
    ViscaCommunication m_visca_comm;
};

#endif // VISCA_H
