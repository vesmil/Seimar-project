#ifndef SUBMENU_H
#define SUBMENU_H

#include "menuElementBase.h"

#include <vector>
#include <memory>

class Submenu : public MenuElementBase
{
public:
    Submenu();

    std::vector<std::shared_ptr<MenuElementBase>> elementList;
};

#endif // SUBMENU_H
