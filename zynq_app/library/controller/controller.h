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

    std::array<std::pair<float, QString>, 6> ZoomArray { std::pair<float, QString>{1, QString("1x")}, std::pair<float, QString>{1.2, QString("1.2x")}, std::pair<float, QString>{1.5, QString("1.5x")},
                                                         std::pair<float, QString>{2, QString("2x")}, std::pair<float, QString>{5, QString("5x")}, std::pair<float, QString>{10, QString("10x")}};
    ArrValue<float, Controller, 6> zoom{&ZoomArray, &Controller::setZoom, this};

    using ModeValue = ArrValue<ViscaCommands::Exposure::Mode, Controller, 5U>;
    ModeValue exposureMode{&ViscaCommands::Exposure::ModeArray, &Controller::setExposureMode, this};

    ValueSetter<uint8_t, uint8_t, Controller> shutter {0, 0, 10, &Controller::setShutter, this, ""};
    Dependency<ModeValue, ViscaCommands::Exposure::Mode, ViscaCommands::Exposure::Mode::MANUAL, ViscaCommands::Exposure::Mode::SHUTTER_PRI> validShutter{exposureMode};

    ValueSetter<uint8_t, uint8_t, Controller> iris {0x10, 0x5, 0x15, &Controller::setIris, this, ""};
    Dependency<ModeValue, ViscaCommands::Exposure::Mode, ViscaCommands::Exposure::Mode::MANUAL, ViscaCommands::Exposure::Mode::IRIS_PRI> validIris{exposureMode};

    ValueSetter<int, int, Controller> gain {0, -3, 33, &Controller::setGain, this, "dB"};
    Dependency<ModeValue, ViscaCommands::Exposure::Mode, ViscaCommands::Exposure::Mode::MANUAL, ViscaCommands::Exposure::Mode::GAIN_PRI> validGain{exposureMode};

    BoolValue<Controller> rtp_stream {false, &Controller::switchRtp, this};
    BoolValue<Controller> file_stream {false, &Controller::switchFile, this};
    BoolValue<Controller> hdmi_stream {false, &Controller::switchHDMI, this};

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

    bool switchRtp(bool state);
    bool switchFile(bool state);
    bool switchHDMI(bool state);

    bool setResolution(ViscaCommands::Hdmi::Format);

    Visca& m_visca;
    GsFacade& m_gstreamer;

    std::queue<std::unique_ptr<IControllerCommand>> commandQueue;
};

#endif // CONTROLLER_H
