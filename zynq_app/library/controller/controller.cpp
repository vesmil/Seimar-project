#include "controller.h"

Controller::Controller(Visca& visca, GsFacade& gstreamer) : m_visca(visca), m_gstreamer(gstreamer)
{
    shutter->addDependency<Controller, ViscaCommands::Exposure::Mode, ViscaCommands::Exposure::Mode::MANUAL, ViscaCommands::Exposure::Mode::SHUTTER_PRI>(exposureMode.get());
    iris->addDependency<Controller, ViscaCommands::Exposure::Mode, ViscaCommands::Exposure::Mode::MANUAL, ViscaCommands::Exposure::Mode::IRIS_PRI>(exposureMode.get());
    gain->addDependency<Controller, ViscaCommands::Exposure::Mode, ViscaCommands::Exposure::Mode::MANUAL, ViscaCommands::Exposure::Mode::GAIN_PRI>(exposureMode.get());

    focusDistance->addDependency<Controller, bool, false>(autofocus.get());

    rGain->addDependency<Controller, ViscaCommands::Color::WhiteBalance::Mode, ViscaCommands::Color::WhiteBalance::Mode::MANUAL>(whiteBalance.get());
    bGain->addDependency<Controller, ViscaCommands::Color::WhiteBalance::Mode, ViscaCommands::Color::WhiteBalance::Mode::MANUAL>(whiteBalance.get());

    setAllDefault();
}

void Controller::addCommandToQueue(std::unique_ptr<IControllerCommand> command)
{
    m_commandQueue.emplace(std::move(command));

    if (!queueExecuting)
    {
        QtConcurrent::run(this, &Controller::startExecutingCommandQueue);
    }
}

bool Controller::setAllDefault()
{
    zoom->setDefault();
    exposureMode->setDefault();

    hdmi_stream->setDefault();
    rtp_stream->setDefault();
    file_stream->setDefault();

    autofocus->setDefault();

    return true;
}

void Controller::startExecutingCommandQueue()
{
    if(queueExecuting)
    {
        return;
    }

    queueExecuting = true;
    while (!m_commandQueue.empty())
    {
        m_commandQueue.front()->execute();
        m_commandQueue.pop();
    }

    queueExecuting = false;
}

bool Controller::setZoom(float zoom)
{
    uint16_t remappedZoom = (zoom / 16.0f) * 0x4000;
    return m_visca.executeCommand(ViscaCommands::Zoom::setValue(remappedZoom),m_viscaWaitTime,"zoom");
}

bool Controller::setExposureMode(ViscaCommands::Exposure::Mode mode)
{
    return m_visca.executeCommand(ViscaCommands::Exposure::setMode(mode),m_viscaWaitTime,"exposure mode");
}

bool Controller::setShutter(u_int8_t value)
{
    return m_visca.executeCommand(ViscaCommands::Exposure::Shutter::setValue(value),m_viscaWaitTime,"shutter");
}

bool Controller::setIris(uint8_t value)
{
    return m_visca.executeCommand(ViscaCommands::Exposure::Iris::setValue(value),m_viscaWaitTime,"iris");
}

bool Controller::setGain(int value)
{
    uint8_t remappedValue = ViscaCommands::mapToNewRange<uint8_t, int>(value, -3, 33,  0, 0x0C);
    return m_visca.executeCommand(ViscaCommands::Exposure::Gain::setValue(remappedValue),m_viscaWaitTime,"gain");
}

bool Controller::setExposureCompensation(uint8_t value) {
    // TODO Do i need to set state before that?
    return m_visca.executeCommand(ViscaCommands::Exposure::Compensation::setValue(value),m_viscaWaitTime,"exposure compensation");
}

bool Controller::setRtp(bool state)
{
    return m_gstreamer.setState(GsFacade::RAW_RTP, state);
}

bool Controller::setFile(bool state)
{
    return m_gstreamer.setState(GsFacade::RAW_SAVE, state);
}

bool Controller::setHDMI(bool state)
{
    return m_gstreamer.setState(GsFacade::RAW_DISPLAY, state);
}

bool Controller::setFormat(ViscaCommands::Hdmi::Format format)
{
    return m_visca.executeCommand(ViscaCommands::Hdmi::setFormat(format), 2000, "Setting res", false);
}

bool Controller::setColorspace(ViscaCommands::Hdmi::Colorspace color)
{
    return m_visca.executeCommand(ViscaCommands::Hdmi::setColorspace(color), 2000, "Setting colorspace", false);
}

bool Controller::setWhitebalance(ViscaCommands::Color::WhiteBalance::Mode mode)
{    /*
    Dependency<ValuePtr, ViscaCommands::Exposure::Mode, ViscaCommands::Exposure::Mode::MANUAL, ViscaCommands::Exposure::Mode::SHUTTER_PRI> m_validShutter{exposureMode.get()};
    Dependency<ValuePtr, ViscaCommands::Exposure::Mode, ViscaCommands::Exposure::Mode::MANUAL, ViscaCommands::Exposure::Mode::IRIS_PRI> m_validIris{exposureMode.get()};
    Dependency<ValuePtr, ViscaCommands::Exposure::Mode, ViscaCommands::Exposure::Mode::MANUAL, ViscaCommands::Exposure::Mode::GAIN_PRI> m_validGain{exposureMode.get()};
    Dependency<ValuePtr, ViscaCommands::Color::WhiteBalance::Mode, ViscaCommands::Color::WhiteBalance::Mode::MANUAL> m_manualWB{whiteBalance.get()};
    Dependency<ValuePtr, bool, false> m_autofocus{autofocus.get()};
    */
    return m_visca.executeCommand(ViscaCommands::Color::WhiteBalance::setMode(mode), m_viscaWaitTime, "White balance");
}

bool Controller::setRGain(uint16_t value)
{
    return m_visca.executeCommand(ViscaCommands::Color::RGain::setValue(value), m_viscaWaitTime, "RGain");
}

bool Controller::setBGain(uint16_t value)
{
    return m_visca.executeCommand(ViscaCommands::Color::BGain::setValue(value), m_viscaWaitTime, "BGain");
}

bool Controller::setAutofocus(bool state)
{
    return m_visca.executeCommand(ViscaCommands::Focus::setFocusMode(state? ViscaCommands::Focus::FocusMode::AUTO : ViscaCommands::Focus::FocusMode::MANUAL), m_viscaWaitTime, "Focus");
}

bool Controller::setFocusDistance(uint16_t distanceValue)
{
    return m_visca.executeCommand(ViscaCommands::Focus::setValue(0x1000 * distanceValue), m_viscaWaitTime, "Focus distance");
}

bool Controller::setbackLightCompensation(bool state)
{
    return m_visca.executeCommand(ViscaCommands::Exposure::backLightCompensation(state? ViscaCommands::State::ON : ViscaCommands::State::OFF), m_viscaWaitTime, "Backlight");
}

bool Controller::setvisibilityEnhancer(bool state)
{
    return m_visca.executeCommand(ViscaCommands::Exposure::visibilityEnhancer(state? ViscaCommands::State::ON : ViscaCommands::State::OFF), m_viscaWaitTime, "Visibility enhancer");
}

bool Controller::setPower(ViscaCommands::State state)
{
    return m_visca.executeCommand(ViscaCommands::Power::setState(state), 2000, "Power");
}

bool Controller::setPower(bool boolState)
{
    ViscaCommands::State state = boolState ? ViscaCommands::State::ON : ViscaCommands::State::OFF;
    return m_visca.executeCommand(ViscaCommands::Power::setState(state), 2000, "Power", false);
}


