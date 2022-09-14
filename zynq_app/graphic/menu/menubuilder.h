#ifndef MENUBUILDER_H
#define MENUBUILDER_H

#include "graphic/menu/items/submenuitem.h"
#include "graphic/menu/items/valueitem.h"
#include "graphic/menu/items/popupitem.h"

#include "library/controller/controller.h"

class MenuBuilder
{
public:
    static void buildMenuTree(Menu& menu, Controller* controller);

private:
    static void buildFunctions(SubmenuItem* submenu, QWidget* parent, Controller* controller);
    static void buildStream(SubmenuItem* submenu, QWidget* parent, Controller* controller);
    static void buildAdvanced(SubmenuItem* submenu, QWidget* parent, Controller* controller);
};

#endif // MENUBUILDER_H
