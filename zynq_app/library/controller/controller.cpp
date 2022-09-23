#include "controller.h"

Controller::Controller(Visca& visca, GsFacade& gstreamer) : m_visca(visca), m_gstreamer(gstreamer)
{
    shutter.addDependency(&validShutter);
    iris.addDependency(&validIris);
    gain.addDependency(&validGain);

    setDefault();
}

void Controller::addCommandToQueue(std::unique_ptr<IControllerCommand> command)
{
    commandQueue.emplace(std::move(command));

    if (!queueExecuting)
    {
        QtConcurrent::run(this, &Controller::startExecutingCommandQueue);
    }
}

bool Controller::setDefault()
{
    zoom.setDefault();
    exposureMode.setDefault();

    rtp_stream.setDefault();
    file_stream.setDefault();
    hdmi_stream.setDefault();

    // setResolution(ViscaCommands::Hdmi::_1920x1080_59_94HZ);
    setColor(ViscaCommands::Hdmi::RGB);

    // qCInfo(viscaLog) << "Color" << m_visca.inquireCommand(ViscaCommands::Hdmi::getColorspace(), ViscaCommands::Hdmi::valueFromReply, 600);

    return true;
}

void Controller::startExecutingCommandQueue()
{
    queueExecuting = true;

    while (!commandQueue.empty())
    {
        commandQueue.front()->execute();
        commandQueue.pop();
    }

    queueExecuting = false;
}

bool Controller::setZoom(float zoom)
{
    uint16_t remappedZoom = (zoom / 16.0f) * 0x4000;
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

bool Controller::setExposureCompensation(uint8_t value) {
    // TODO Do i need to set state before that?
    return m_visca.executeCommand(ViscaCommands::Exposure::Compensation::setValue(value),400,"exposure compensation");
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

bool Controller::setResolution(ViscaCommands::Hdmi::Format format)
{
    m_visca.executeCommand(ViscaCommands::Power::setState(ViscaCommands::State::OFF), 2000, "shutting of");
    m_visca.executeCommand(ViscaCommands::Hdmi::setFormat(format), 2000, "Setting res", false);
    m_visca.executeCommand(ViscaCommands::Power::setState(ViscaCommands::State::ON), 2000, "starting");

    return true;
}

bool Controller::setColor(ViscaCommands::Hdmi::Colorspace color)
{
    m_visca.executeCommand(ViscaCommands::Power::setState(ViscaCommands::State::OFF), 2000, "shutting of");
    m_visca.executeCommand(ViscaCommands::Hdmi::setColorspace(color), 2000, "Setting color", false);
    m_visca.executeCommand(ViscaCommands::Power::setState(ViscaCommands::State::ON), 2000, "starting");

    return true;
}


