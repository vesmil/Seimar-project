#ifndef MENUBUILDER_H
#define MENUBUILDER_H

#include "graphic/menu/menu.h"
#include "library/controller/controller.h"

class MenuBuilder
{
public:
    static void buildMenuTree(Menu& menu, Controller* controller);

private:
    static std::unique_ptr<SubmenuItem> buildFunctions(SubmenuItem* parentMenu, QWidget* parentWidget, Controller* controller);
    static std::unique_ptr<SubmenuItem> buildStream(SubmenuItem* parentMenu, QWidget* parentWidget, Controller* controller);
    static std::unique_ptr<SubmenuItem> buildAdvanced(SubmenuItem* parentMenu, QWidget* parentWidget, Controller* controller);
};

#endif // MENUBUILDER_H
