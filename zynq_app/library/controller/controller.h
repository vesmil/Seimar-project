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

    Value<uint8_t, Controller> zoom {0, 0, 10, &Controller::setZoom, this, "x"};

    Value<ViscaCommands::Exposure::Mode, Controller> exposureMode
    {ViscaCommands::Exposure::Mode::FULL_AUTO, ViscaCommands::Exposure::Mode::FULL_AUTO, ViscaCommands::Exposure::Mode::SHUTTER_PRI, &Controller::setExposureMode, this, "x"};

private:
    bool setDefault();

    bool setZoom(uint8_t value);
    bool setExposureMode(ViscaCommands::Exposure::Mode mode);

    // TODO add exposure check
    bool setIris(uint8_t value);
    bool setGain(u_int8_t value);
    bool setShutter(u_int8_t value);
    bool setExposureCompensation(uint8_t value);

    Visca& m_visca;
};

#endif // CONTROLLER_H
