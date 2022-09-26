#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "library/visible/visca/visca.h"
#include "library/visible/visca/viscaCommands.h"
#include "library/visible/gstreamer/gsfacade.h"

#include "library/controller/value.h"
#include "library/controller/controllercommand.h"

#include <QFuture>
#include <QtConcurrent/QtConcurrent>
#include <queue>

//! \brief Proxy that links all modules together
class Controller
{
public:
    Controller(Visca& visca, GsFacade& gstreamer);
    void addCommandToQueue(std::unique_ptr<IControllerCommand> command);

    using ModeValue = ArrValue<ViscaCommands::Exposure::Mode, Controller, 5U>;
    ModeValue exposureMode{&ViscaCommands::Exposure::ModeArray, &Controller::setExposureMode, this};

    ArrValue<float, Controller, 6> zoom{&m_zoomArray, &Controller::setZoom, this};
    ValueSetter<uint8_t, uint8_t, Controller> shutter {0, 0, 10, &Controller::setShutter, this, ""};
    ValueSetter<uint8_t, uint8_t, Controller> iris {0x10, 0x5, 0x15, &Controller::setIris, this, ""};
    ValueSetter<int, int, Controller> gain {0, -3, 33, &Controller::setGain, this, "dB"};

    BoolValue<Controller> standby {true, &Controller::setPower, this};

    // NOTE probably should be saved somewhere
    ArrValue<ViscaCommands::Hdmi::Format, Controller, ViscaCommands::Hdmi::FormatCount> format{&ViscaCommands::Hdmi::FormatArray, &Controller::setFormat, this};
    ArrValue<ViscaCommands::Hdmi::Colorspace, Controller, ViscaCommands::Hdmi::ColorspaceCount> colorspace{&ViscaCommands::Hdmi::ColorSpaceArray, &Controller::setColorspace, this};

    ArrValue<ViscaCommands::Color::WhiteBalance::Mode, Controller, ViscaCommands::Color::WhiteBalance::ModeCount> whiteBalance{&ViscaCommands::Color::WhiteBalance::ModeArray, &Controller::setWhitebalance, this};

    BoolValue<Controller> focusMode {true, &Controller::setAutofocus, this, "Auto", "Manual"};
    ValueSetter<uint16_t, uint16_t, Controller> focusDistance {0, 0, 10, &Controller::setFocusDistance, this, ""};

    // Dependency

    // White balance
    // Focus
    // Compensation
    // backLightCompensation
    // visibilityEnhancer

    // Color...

    BoolValue<Controller> rtp_stream {true, &Controller::setRtp, this};
    BoolValue<Controller> file_stream {false, &Controller::setFile, this};
    BoolValue<Controller> hdmi_stream {false, &Controller::setHDMI, this};

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
    bool setAutofocus(bool state);

    bool setFocusDistance(uint16_t distance);
    bool setCompensation();

    // Focus
    // Compensation
    // backLightCompensation
    // visibilityEnhancer

    // Color...

    static const uint m_viscaWaitTime = 400;

    Visca& m_visca;
    GsFacade& m_gstreamer;

    std::queue<std::unique_ptr<IControllerCommand>> m_commandQueue;

    std::array<std::pair<float, QString>, 6> m_zoomArray { std::pair<float, QString>{1, QString("1x")}, std::pair<float, QString>{1.2, QString("1.2x")}, std::pair<float, QString>{1.5, QString("1.5x")},
                                                         std::pair<float, QString>{2, QString("2x")}, std::pair<float, QString>{5, QString("5x")}, std::pair<float, QString>{10, QString("10x")}};

    Dependency<ModeValue, ViscaCommands::Exposure::Mode, ViscaCommands::Exposure::Mode::MANUAL, ViscaCommands::Exposure::Mode::SHUTTER_PRI> m_validShutter{exposureMode};
    Dependency<ModeValue, ViscaCommands::Exposure::Mode, ViscaCommands::Exposure::Mode::MANUAL, ViscaCommands::Exposure::Mode::IRIS_PRI> m_validIris{exposureMode};
    Dependency<ModeValue, ViscaCommands::Exposure::Mode, ViscaCommands::Exposure::Mode::MANUAL, ViscaCommands::Exposure::Mode::GAIN_PRI> m_validGain{exposureMode};
    Dependency<BoolValue<Controller>, bool, false> m_cameraOff{standby};
};

#endif // CONTROLLER_H
