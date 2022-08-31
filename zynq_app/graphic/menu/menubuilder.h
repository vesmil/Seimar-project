#ifndef MENUBUILDER_H
#define MENUBUILDER_H

#include "graphic/menu/items/submenuitem.h"
#include "graphic/menu/items/valueitem.h"
#include "graphic/menu/items/popupitem.h"

#include "library/controller/controller.h"

class MenuBuilder
{
public:
    static void buildMenuTree(SubmenuItem* root, QWidget* parent, Controller* controller);

private:
    // buildSubmenu...();
    // buildSubmenu...();
    // ...

    // root and parent member vars?
};

#endif // MENUBUILDER_H
