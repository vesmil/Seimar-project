#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "library/visible/visca/visca.h"
#include "library/visible/visca/viscaCommands.h"

#include "library/controller/value.h"

/*!
 * \brief Proxy class that will link all modules together
 */
class Controller
{
public:
    Controller(Visca& visca);

    NumValue<uint8_t, uint8_t, Controller> zoom {0, 0, 10, &Controller::setZoom, this, "x"};

    ArrValue<ViscaCommands::Exposure::Mode, 5U, Controller> exposureMode{&ViscaCommands::Exposure::ModeArray, &Controller::setExposureMode, this};

    NumValue<uint8_t, uint8_t, Controller> shutter {0, 0, 10, &Controller::setShutter, this, ""};
    Dependency<NumValue<uint8_t, uint8_t, Controller>, ViscaCommands::Exposure::Mode, ViscaCommands::Exposure::Mode::MANUAL, ViscaCommands::Exposure::Mode::SHUTTER_PRI> validShutter{shutter};

    NumValue<uint8_t, uint8_t, Controller> iris {0x10, 0x5, 0x15, &Controller::setIris, this, ""};
    NumValue<uint8_t, uint8_t, Controller> gain {0, 6, 0x0C, &Controller::setGain, this, "dB"};

private:
    bool setDefault();

    bool setZoom(uint8_t value);
    bool setExposureMode(ViscaCommands::Exposure::Mode mode);

    // TODO add exposure check
    bool setShutter(u_int8_t value);
    bool setIris(uint8_t value);
    bool setGain(u_int8_t value);

    bool setExposureCompensation(uint8_t value);

    Visca& m_visca;
};

#endif // CONTROLLER_H
