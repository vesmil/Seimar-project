#include "controller.h"
#include "global/config.h"

Controller::Controller(Visca& visca) : m_visca(visca)
{
    setDefault();
}

bool Controller::setDefault()
{
    setZoom(0);
    setExposureMode(ViscaCommands::Exposure::Mode::FULL_AUTO);
    // ...

    return false;
}

//! \brief zoom in range 0-10
bool Controller::setZoom(uint8_t zoom)
{
    uint16_t remappedZoom = (zoom * 0x4000) / 16;
    return m_visca.executeCommand(ViscaCommands::Zoom::setValue(remappedZoom),400,"zoom");
}

bool Controller::setExposureMode(ViscaCommands::Exposure::Mode mode)
{
    return m_visca.executeCommand(ViscaCommands::Exposure::setMode(mode),400,"exposure mode");
}

