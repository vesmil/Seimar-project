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

/*!
 * \brief Proxy linking all modules together
 * \note It almost becomes an anti-pattern here, but there is no better option to link all modules with menu and other ways of controlling the camera
 */
class Controller
{
    template<typename T>
    using SetPtr = std::unique_ptr<Setter<T,Controller>>;

public:
    Controller(Visca& visca, GsFacade& gstreamer);
    void addCommandToQueue(std::unique_ptr<IControllerCommand> command);

    SetPtr<float> zoom = makeArrValue(ViscaCommands::Zoom::zoomArray, &Controller::setZoom, this);

    SetPtr<ViscaCommands::Exposure::Mode> exposureMode = makeArrValue(ViscaCommands::Exposure::ModeArray, &Controller::setExposureMode, this);
    SetPtr<uint8_t> shutter = makeIntValue<uint8_t>(0, 0, 10, &Controller::setShutter, this);
    SetPtr<uint8_t> iris = makeIntValue<uint8_t>(0x10, 0x5, 0x15, &Controller::setIris, this);
    SetPtr<int> gain = makeIntValue<int>(0, -3, 33, &Controller::setGain, this, "dB");

    SetPtr<bool> power = makeBoolValue(true, &Controller::setPower, this);

    SetPtr<ViscaCommands::Hdmi::Format> format = makeArrValue(ViscaCommands::Hdmi::FormatArray, &Controller::setFormat, this);
    SetPtr<ViscaCommands::Hdmi::Colorspace> colorspace = makeArrValue(ViscaCommands::Hdmi::ColorSpaceArray, &Controller::setColorspace, this);

    SetPtr<ViscaCommands::Color::WhiteBalance::Mode> whiteBalance = makeArrValue(ViscaCommands::Color::WhiteBalance::ModeArray, &Controller::setWhitebalance, this);
    SetPtr<uint16_t> rGain = makeIntValue<uint16_t>(200, 0, 0xFF, &Controller::setRGain, this);
    SetPtr<uint16_t> bGain = makeIntValue<uint16_t>(200, 0, 0xFF, &Controller::setBGain, this);

    SetPtr<bool> autofocus = makeBoolValue(true, &Controller::setAutofocus, this, "Auto", "Manual");
    SetPtr<uint16_t> focusDistance = makeIntValue<uint16_t>(0xB, 0x1, 0xF, &Controller::setFocusDistance, this);

    SetPtr<bool> visibilityEnhancer = makeBoolValue(false, &Controller::setvisibilityEnhancer, this);
    SetPtr<bool> backLight = makeBoolValue(false, &Controller::setbackLightCompensation, this);

    SetPtr<bool> rtp_stream = makeBoolValue(true, &Controller::setRtp, this);
    SetPtr<bool> file_stream = makeBoolValue(false, &Controller::setFile, this);
    SetPtr<bool> hdmi_stream = makeBoolValue(true, &Controller::setHDMI, this);

    bool setAllDefault();

private:
    void startExecutingCommandQueue();
    std::atomic_bool queueExecuting{false};

    // TODO many of the functions are not necesseary as it is copy paste of m_visca...

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

    // TODO compensation, color...

    static const uint m_viscaWaitTime = 800;

    Visca& m_visca;
    GsFacade& m_gstreamer;

    std::queue<std::unique_ptr<IControllerCommand>> m_commandQueue;
};

#endif // CONTROLLER_H
