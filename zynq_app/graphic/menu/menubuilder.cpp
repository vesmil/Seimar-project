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
    submenu->itemList.emplace_back(std::make_unique<ValueItem>("Zoom", controller->zoom, parent, true));
    submenu->itemList.emplace_back(std::make_unique<ValueItem>("Exposure mode", controller->exposureMode, parent));
    submenu->itemList.emplace_back(std::make_unique<ValueItem>("Shutter", controller->shutter, parent));
    submenu->itemList.emplace_back(std::make_unique<ValueItem>("Iris", controller->iris, parent));
    submenu->itemList.emplace_back(std::make_unique<ValueItem>("Gain", controller->gain, parent));

    // TODO add compensation and others
}

void MenuBuilder::buildStream(SubmenuItem* submenu, QWidget* parent, Controller* controller)
{
    submenu->itemList.emplace_back(std::make_unique<ValueItem>("Display", controller->hdmi_stream, parent));
    submenu->itemList.emplace_back(std::make_unique<ValueItem>("RTP", controller->rtp_stream, parent));
    submenu->itemList.emplace_back(std::make_unique<ValueItem>("File", controller->file_stream, parent));
}

void MenuBuilder::buildAdvanced(SubmenuItem* submenu, QWidget* parent, Controller*) //controller)
{
    QWidget* widget = new QLabel("...");
    submenu->itemList.emplace_back(std::make_unique<PopupItem>("test", widget, parent));
    submenu->itemList.emplace_back(std::make_unique<PopupItem>("test 2", widget, parent));
}

