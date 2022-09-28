#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "library/visible/visca/visca.h"
#include "library/visible/visca/viscaCommands.h"
#include "library/visible/gstreamer/gsfacade.h"
#include "library/controller/elements/setter.h"
#include "library/controller/elements/controllercommand.h"
#include "global/utility.h"

#include <QFuture>
#include <QtConcurrent/QtConcurrent>
#include <queue>

// NOTE controller becomes sort of an anti-pattern herebut I need some part linking all modules together

//! \brief Proxy that links all modules together
class Controller
{
    using ValuePtr = std::unique_ptr<ISetter>;

public:
    Controller(Visca& visca, GsFacade& gstreamer);
    void addCommandToQueue(std::unique_ptr<IControllerCommand> command);

    ValuePtr zoom = makeArrValue(ViscaCommands::Zoom::zoomArray, &Controller::setZoom, this);

    ValuePtr exposureMode = makeArrValue(ViscaCommands::Exposure::ModeArray, &Controller::setExposureMode, this);
    ValuePtr shutter = makeIntValue<uint8_t>(0, 0, 10, &Controller::setShutter, this);
    ValuePtr iris = makeIntValue<uint8_t>(0x10, 0x5, 0x15, &Controller::setIris, this);
    ValuePtr gain = makeIntValue<int>(0, -3, 33, &Controller::setGain, this, "dB");

    ValuePtr power = makeBoolValue(true, &Controller::setPower, this);

    ValuePtr format = makeArrValue(ViscaCommands::Hdmi::FormatArray, &Controller::setFormat, this);
    ValuePtr colorspace = makeArrValue(ViscaCommands::Hdmi::ColorSpaceArray, &Controller::setColorspace, this);

    ValuePtr whiteBalance = makeArrValue(ViscaCommands::Color::WhiteBalance::ModeArray, &Controller::setWhitebalance, this);
    ValuePtr rGain = makeIntValue<uint16_t>(200, 0, 0xFF, &Controller::setRGain, this);
    ValuePtr bGain = makeIntValue<uint16_t>(200, 0, 0xFF, &Controller::setBGain, this);

    ValuePtr autofocus = makeBoolValue(true, &Controller::setAutofocus, this, "Auto", "Manual");
    ValuePtr focusDistance = makeIntValue<uint16_t>(0xB, 0x1, 0xF, &Controller::setFocusDistance, this);

    ValuePtr visibilityEnhancer = makeBoolValue(false, &Controller::setvisibilityEnhancer, this, "Auto", "Manual");
    // TODO visibilityLevel
    ValuePtr backLight = makeBoolValue(false, &Controller::setbackLightCompensation, this, "Auto", "Manual");

    ValuePtr rtp_stream = makeBoolValue(true, &Controller::setRtp, this);
    ValuePtr file_stream = makeBoolValue(false, &Controller::setFile, this);
    ValuePtr hdmi_stream = makeBoolValue(true, &Controller::setHDMI, this);

private:
    void startExecutingCommandQueue();
    std::atomic_bool queueExecuting{false};

    bool setDefault();

    bool setZoom(float value);
    bool setExposureMode(ViscaCommands::Exposure::Mode mode);
    bool setShutter(u_int8_t value);
    bool setIris(uint8_t value);
    bool setGain(int value);
    bool setExposureCompensation(uint8_t value);

    bool setRtp(bool state);
    bool setFile(bool state);
    bool setHDMI(bool state);

    bool setFormat(ViscaCommands::Hdmi::Format format);
    bool setColorspace(ViscaCommands::Hdmi::Colorspace colorspace);

    bool setPower(ViscaCommands::State state);
    bool setPower(bool boolState);

    bool setWhitebalance(ViscaCommands::Color::WhiteBalance::Mode mode);
    bool setRGain(uint16_t value);
    bool setBGain(uint16_t value);

    bool setAutofocus(bool state);
    bool setFocusDistance(uint16_t distance);

    bool setbackLightCompensation(bool state);
    bool setvisibilityEnhancer(bool state);

    // TODO
    bool setCompensation();

    // Color...

    static const uint m_viscaWaitTime = 400;

    Visca& m_visca;
    GsFacade& m_gstreamer;

    std::queue<std::unique_ptr<IControllerCommand>> m_commandQueue;

    /*
    Dependency<ValuePtr, ViscaCommands::Exposure::Mode, ViscaCommands::Exposure::Mode::MANUAL, ViscaCommands::Exposure::Mode::SHUTTER_PRI> m_validShutter{exposureMode.get()};
    Dependency<ValuePtr, ViscaCommands::Exposure::Mode, ViscaCommands::Exposure::Mode::MANUAL, ViscaCommands::Exposure::Mode::IRIS_PRI> m_validIris{exposureMode.get()};
    Dependency<ValuePtr, ViscaCommands::Exposure::Mode, ViscaCommands::Exposure::Mode::MANUAL, ViscaCommands::Exposure::Mode::GAIN_PRI> m_validGain{exposureMode.get()};
    Dependency<ValuePtr, ViscaCommands::Color::WhiteBalance::Mode, ViscaCommands::Color::WhiteBalance::Mode::MANUAL> m_manualWB{whiteBalance.get()};
    Dependency<ValuePtr, bool, false> m_autofocus{autofocus.get()};
    */
};

#endif // CONTROLLER_H
