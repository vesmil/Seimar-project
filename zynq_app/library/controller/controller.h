#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "library/visible/visca/visca.h"
#include "library/visible/visca/viscaCommands.h"
/*!
 * \brief Proxy class that will link all modules together
 */
class Controller
{
public:
    Controller(Visca& visca);

    bool setDefault();
    bool setZoom(int zoom);

    Visca& m_visca;
};

#endif // CONTROLLER_H
