#include "menubuilder.h"

#include "library/application/settings.h"
#include "library/controller/controller.h"

void MenuBuilder::buildMenuTree(Menu &menu, Controller* controller)
{
    SubmenuItem* root = menu.getRoot();
    QWidget* parent = static_cast<QWidget*>(&menu);

    root->m_itemList.emplace_back(std::make_unique<SubmenuItem>("Functions", root, parent));
    buildFunctions(static_cast<SubmenuItem*>((root->m_itemList[0]).get()), parent, controller);

    root->m_itemList.emplace_back(std::make_unique<SubmenuItem>("Stream", root, parent));
    buildStream(static_cast<SubmenuItem*>((root->m_itemList[1]).get()), parent, controller);

    root->m_itemList.emplace_back(std::make_unique<SubmenuItem>("Advanced", root, parent));
    buildAdvanced(static_cast<SubmenuItem*>((root->m_itemList[2]).get()), parent, controller);
}

void MenuBuilder::buildFunctions(SubmenuItem* submenu, QWidget* parent, Controller* controller)
{
    submenu->m_itemList.emplace_back(std::make_unique<ValueItem>("Zoom", controller->zoom, submenu, parent, true));
    submenu->m_itemList.emplace_back(std::make_unique<ValueItem>("Exposure mode", controller->exposureMode, submenu, parent));
    submenu->m_itemList.emplace_back(std::make_unique<ValueItem>("Shutter", controller->shutter, submenu, parent));
    submenu->m_itemList.emplace_back(std::make_unique<ValueItem>("Iris", controller->iris, submenu, parent));
    submenu->m_itemList.emplace_back(std::make_unique<ValueItem>("Gain", controller->gain, submenu, parent));
    // TODO add compensation and other items
}

void MenuBuilder::buildStream(SubmenuItem* submenu, QWidget* parent, Controller* controller)
{
    submenu->m_itemList.emplace_back(std::make_unique<ValueItem>("Display", controller->hdmi_stream, submenu, parent));
    submenu->m_itemList.emplace_back(std::make_unique<ValueItem>("RTP", controller->rtp_stream, submenu, parent));
    submenu->m_itemList.emplace_back(std::make_unique<ValueItem>("File", controller->file_stream, submenu, parent));
}

void MenuBuilder::buildAdvanced(SubmenuItem* submenu, QWidget* parent, Controller*)
{
    // NOTE remove these dangling pointers
    ControlableWidget* widget = new ControlableWidget("...", parent);

    submenu->m_itemList.emplace_back(std::make_unique<PopupItem>("test", widget, submenu, parent));
    submenu->m_itemList.emplace_back(std::make_unique<PopupItem>("test 2", widget, submenu, parent));
}

