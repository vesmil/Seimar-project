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
    using ValPtr = std::unique_ptr<ValueSetter<T,Controller>>;

public:
    Controller(Visca& visca, GsFacade& gstreamer);
    void addCommandToQueue(std::unique_ptr<IControllerCommand> command);

    ValPtr<float> zoom = makeArrValue(ViscaCommands::Zoom::zoomArray, &Controller::setZoom, this);

    ValPtr<ViscaCommands::Exposure::Mode> exposureMode = makeArrValue(ViscaCommands::Exposure::ModeArray, &Controller::setExposureMode, this);
    ValPtr<uint8_t> shutter = makeIntValue<uint8_t>(0, 0, 10, &Controller::setShutter, this);
    ValPtr<uint8_t> iris = makeIntValue<uint8_t>(0x10, 0x5, 0x15, &Controller::setIris, this);
    ValPtr<int> gain = makeIntValue<int>(0, -3, 33, &Controller::setGain, this, "dB");

    ValPtr<bool> power = makeBoolValue(true, &Controller::setPower, this);

    ValPtr<ViscaCommands::Hdmi::Format> format = makeArrValue(ViscaCommands::Hdmi::FormatArray, &Controller::setFormat, this);
    ValPtr<ViscaCommands::Hdmi::Colorspace> colorspace = makeArrValue(ViscaCommands::Hdmi::ColorSpaceArray, &Controller::setColorspace, this);

    ValPtr<ViscaCommands::Color::WhiteBalance::Mode> whiteBalance = makeArrValue(ViscaCommands::Color::WhiteBalance::ModeArray, &Controller::setWhitebalance, this);
    ValPtr<uint16_t> rGain = makeIntValue<uint16_t>(200, 0, 0xFF, &Controller::setRGain, this);
    ValPtr<uint16_t> bGain = makeIntValue<uint16_t>(200, 0, 0xFF, &Controller::setBGain, this);

    ValPtr<bool> autofocus = makeBoolValue(true, &Controller::setAutofocus, this, "Auto", "Manual");
    ValPtr<uint16_t> focusDistance = makeIntValue<uint16_t>(0xB, 0x1, 0xF, &Controller::setFocusDistance, this);

    ValPtr<bool> visibilityEnhancer = makeBoolValue(false, &Controller::setvisibilityEnhancer, this);
    ValPtr<bool> backLight = makeBoolValue(false, &Controller::setbackLightCompensation, this);

    ValPtr<bool> rtp_stream = makeBoolValue(false, &Controller::setRtp, this);
    ValPtr<bool> file_stream = makeBoolValue(false, &Controller::setFile, this);
    ValPtr<bool> hdmi_stream = makeBoolValue(true, &Controller::setHDMI, this);

    bool setAllDefault();

private:
    void startExecutingCommandQueue();
    std::atomic_bool queueExecuting{false};

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
