#include "controller.h"

#include <library/application/settings.h>

Controller::Controller(Visca& visca) : m_visca(visca)
{
    setDefault();
}

bool Controller::setDefault()
{
    // settings.setdefault
    // visca send all...
    // menu refresh

    Settings::getInstance().visca.zoom = 0;
    m_visca.executeCommand(ViscaCommands::Zoom::setValue(0),400,"zooming");

    return false;
}

// ...zoom in range 0-16
bool Controller::setZoom(int zoom)
{
    return m_visca.executeCommand(ViscaCommands::Zoom::setValue(zoom * 0x400),400,"zooming");
}


