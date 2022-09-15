#include "settings.h"

Settings& Settings::getInstance()
{
    static Settings instance;
    return instance;
}
