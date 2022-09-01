#include "value.h"

#include "library/controller/controller.h"
#include "library/visible/visca/viscaCommands.h"

template<>
QString Value<ViscaCommands::Exposure::Mode, Controller>::getQString()
{
    return ViscaCommands::Exposure::ModeToQString(m_value);
}

// TODO redo this #$! with array...
template<>
void Value<ViscaCommands::Exposure::Mode, Controller>::operator++()
{
    switch(m_value){
        case ViscaCommands::Exposure::FULL_AUTO:
            m_value = ViscaCommands::Exposure::MANUAL;
            break;
        case ViscaCommands::Exposure::MANUAL:
            m_value = ViscaCommands::Exposure::SHUTTER_PRI;
            break;
        case ViscaCommands::Exposure::SHUTTER_PRI:
            m_value = ViscaCommands::Exposure::IRIS_PRI;
            break;
        case ViscaCommands::Exposure::IRIS_PRI:
            m_value = ViscaCommands::Exposure::GAIN_PRI;
            break;
        case ViscaCommands::Exposure::GAIN_PRI:
            m_value = ViscaCommands::Exposure::FULL_AUTO;
            break;
    }
}

template<>
void Value<ViscaCommands::Exposure::Mode, Controller>::operator--()
{
    switch(m_value){
        case ViscaCommands::Exposure::FULL_AUTO:
            m_value = ViscaCommands::Exposure::SHUTTER_PRI;
            break;
        case ViscaCommands::Exposure::MANUAL:
            m_value = ViscaCommands::Exposure::IRIS_PRI;
            break;
        case ViscaCommands::Exposure::SHUTTER_PRI:
            m_value = ViscaCommands::Exposure::GAIN_PRI;
            break;
        case ViscaCommands::Exposure::IRIS_PRI:
            m_value = ViscaCommands::Exposure::FULL_AUTO;
            break;
        case ViscaCommands::Exposure::GAIN_PRI:
            m_value = ViscaCommands::Exposure::MANUAL;
            break;
    }
}
