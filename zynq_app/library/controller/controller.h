#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "library/visible/visca/visca.h"
#include "library/visible/visca/viscaCommands.h"
#include "library/controller/value.h"
#include "library/visible/gstreamer/gsfacade.h"

/*!
 * \brief Proxy class that will link all modules together
 */
class Controller
{
public:
    Controller(Visca& visca, GsFacade& gstreamer);

    // TODO create as ArrValue
    Value<uint8_t, uint8_t, Controller> zoom {0, 0, 10, &Controller::setZoom, this, "x"};

    using ModeValue = ArrValue<ViscaCommands::Exposure::Mode, Controller, 5U>;
    ModeValue exposureMode{&ViscaCommands::Exposure::ModeArray, &Controller::setExposureMode, this};

    Value<uint8_t, uint8_t, Controller> shutter {0, 0, 10, &Controller::setShutter, this, ""};
    Dependency<ModeValue, ViscaCommands::Exposure::Mode, ViscaCommands::Exposure::Mode::MANUAL, ViscaCommands::Exposure::Mode::SHUTTER_PRI> validShutter{exposureMode};

    Value<uint8_t, uint8_t, Controller> iris {0x10, 0x5, 0x15, &Controller::setIris, this, ""};
    Dependency<ModeValue, ViscaCommands::Exposure::Mode, ViscaCommands::Exposure::Mode::MANUAL, ViscaCommands::Exposure::Mode::IRIS_PRI> validIris{exposureMode};

    Value<int, int, Controller> gain {0, -3, 33, &Controller::setGain, this, "dB"};
    Dependency<ModeValue, ViscaCommands::Exposure::Mode, ViscaCommands::Exposure::Mode::MANUAL, ViscaCommands::Exposure::Mode::GAIN_PRI> validGain{exposureMode};

    BoolValue<Controller> rtp_stream {false, &Controller::switchRtp, this};
    BoolValue<Controller> file_stream {false, &Controller::switchFile, this};
    BoolValue<Controller> hdmi_stream {false, &Controller::switchHDMI, this};

private:
    bool setDefault();

    bool setZoom(uint8_t value);
    bool setExposureMode(ViscaCommands::Exposure::Mode mode);

    bool setShutter(u_int8_t value);
    bool setIris(uint8_t value);
    bool setGain(int value);

    bool setExposureCompensation(uint8_t value);

    bool switchRtp(bool state);
    bool switchFile(bool state);
    bool switchHDMI(bool state);

    Visca& m_visca;
    GsFacade& m_gstreamer;
};

#endif // CONTROLLER_H
