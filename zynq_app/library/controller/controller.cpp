#include "controller.h"

Controller::Controller(Visca& visca, GsFacade& gstreamer) : m_visca(visca), m_gstreamer(gstreamer)
{
    shutter.addDependency(&validShutter);
    iris.addDependency(&validIris);
    gain.addDependency(&validGain);

    setDefault();
}

bool Controller::setDefault()
{
    // TODO...
    zoom.setDefault();
    exposureMode.setDefault();

    rtp_stream.setDefault();
    file_stream.setDefault();
    hdmi_stream.setDefault();

    return true;
}

void Controller::addToViscaQueue(/* Visca set function pointer */) // prob will be template
{
    // TODO should queue be in controller or in Visca
    // ...I guess Visca would make more sense

    // NOTE there could be some optimatizations in the future - check for same commands and skip them
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
    return m_visca.executeCommand(ViscaCommands::Exposure::Iris::setValue(value),400,"iris");
}

bool Controller::setGain(int value)
{
    uint8_t remappedValue = ViscaCommands::mapToNewRange<uint8_t, int>(value, -3, 33,  0, 0x0C);
    return m_visca.executeCommand(ViscaCommands::Exposure::Gain::setValue(remappedValue),400,"gain");
}

bool Controller::switchRtp(bool state)
{
    return m_gstreamer.setState(GsFacade::WIRIS_RTP, state);
}

bool Controller::switchFile(bool state)
{
    return m_gstreamer.setState(GsFacade::RAW_SAVE, state);
}

bool Controller::switchHDMI(bool state)
{
    return m_gstreamer.setState(GsFacade::RAW_DISPLAY, state);
}

bool Controller::setExposureCompensation(uint8_t value) {
    return false;
}

