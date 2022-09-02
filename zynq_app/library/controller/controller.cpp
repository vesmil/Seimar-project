#include "controller.h"
#include "global/config.h"

Controller::Controller(Visca& visca) : m_visca(visca)
{
    shutter.addDependency(validShutter);

    setDefault();
}

bool Controller::setDefault()
{
    setZoom(0);
    setExposureMode(ViscaCommands::Exposure::Mode::FULL_AUTO);
    // ...

    return false;
}

bool Controller::setZoom(uint8_t zoom)
{
    uint16_t remappedZoom = (zoom * 0x4000) / 16;
    return m_visca.executeCommand(ViscaCommands::Zoom::setValue(remappedZoom),400,"zoom");
}

bool Controller::setExposureMode(ViscaCommands::Exposure::Mode mode)
{
    return m_visca.executeCommand(ViscaCommands::Exposure::setMode(mode),400,"exposure mode");
}

bool Controller::setShutter(u_int8_t value)
{
    return m_visca.executeCommand(ViscaCommands::Exposure::Shutter::setValue(value),400,"shutter");
}

bool Controller::setIris(uint8_t value)
{
    // TODO find out why no more than 17
    return m_visca.executeCommand(ViscaCommands::Exposure::Iris::setValue(value),400,"iris");
}

bool Controller::setGain(u_int8_t value)
{
    // TODO add remaping to db
    return m_visca.executeCommand(ViscaCommands::Exposure::Gain::setValue(value),400,"gain");
}

