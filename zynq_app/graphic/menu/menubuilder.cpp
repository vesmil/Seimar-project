#include "menubuilder.h"

#include "library/application/settings.h"
#include "library/controller/controller.h"

void MenuBuilder::buildMenuTree(Menu &menu, Controller* controller)
{
    SubmenuItem* root = menu.getRoot();
    QWidget* parent = static_cast<QWidget*>(&menu);

    root->itemList.emplace_back(std::make_unique<SubmenuItem>("Functions", root, parent));
    buildFunctions(static_cast<SubmenuItem*>((root->itemList[0]).get()), parent, controller);

    root->itemList.emplace_back(std::make_unique<SubmenuItem>("Stream", root, parent));
    buildStream(static_cast<SubmenuItem*>((root->itemList[1]).get()), parent, controller);

    root->itemList.emplace_back(std::make_unique<SubmenuItem>("Advanced", root, parent));
    buildAdvanced(static_cast<SubmenuItem*>((root->itemList[2]).get()), parent, controller);
}

void MenuBuilder::buildFunctions(SubmenuItem* submenu, QWidget* parent, Controller* controller)
{
    submenu->itemList.emplace_back(std::make_unique<ValueItem>("Zoom", controller->zoom, submenu, parent, true));
    submenu->itemList.emplace_back(std::make_unique<ValueItem>("Exposure mode", controller->exposureMode, submenu, parent));
    submenu->itemList.emplace_back(std::make_unique<ValueItem>("Shutter", controller->shutter, submenu, parent));
    submenu->itemList.emplace_back(std::make_unique<ValueItem>("Iris", controller->iris, submenu, parent));
    submenu->itemList.emplace_back(std::make_unique<ValueItem>("Gain", controller->gain, submenu, parent));

    // TODO add compensation and others
}

void MenuBuilder::buildStream(SubmenuItem* submenu, QWidget* parent, Controller* controller)
{
    submenu->itemList.emplace_back(std::make_unique<ValueItem>("Display", controller->hdmi_stream, submenu, parent));
    submenu->itemList.emplace_back(std::make_unique<ValueItem>("RTP", controller->rtp_stream, submenu, parent));
    submenu->itemList.emplace_back(std::make_unique<ValueItem>("File", controller->file_stream, submenu, parent));
}

void MenuBuilder::buildAdvanced(SubmenuItem* submenu, QWidget* parent, Controller*)
{
    // NOTE remove these dangling pointers
    ControlableWidget* widget = new ControlableWidget("...", parent);

    submenu->itemList.emplace_back(std::make_unique<PopupItem>("test", widget, submenu, parent));
    submenu->itemList.emplace_back(std::make_unique<PopupItem>("test 2", widget, submenu, parent));
}

