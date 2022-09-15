#include "menubuilder.h"

#include "library/application/settings.h"
#include "library/controller/controller.h"

void MenuBuilder::buildMenuTree(Menu &menu, Controller* controller)
{
    SubmenuItem* root = menu.getRoot();
    QWidget* parent = static_cast<QWidget*>(&menu);

    root->addItem(buildFunctions(root, parent, controller));
    root->addItem(buildStream(root, parent, controller));
    root->addItem(buildAdvanced(root, parent, controller));
}

std::unique_ptr<SubmenuItem> MenuBuilder::buildFunctions(SubmenuItem* parentMenu, QWidget* parentWidget, Controller* controller)
{
    auto functionMenu = std::make_unique<SubmenuItem>("Functions", parentMenu, parentWidget);

    functionMenu->addItem(std::make_unique<ValueItem>("Zoom", controller->zoom, functionMenu.get(), parentWidget, true));
    functionMenu->addItem(std::make_unique<ValueItem>("Exposure mode", controller->exposureMode, functionMenu.get(), parentWidget));
    functionMenu->addItem(std::make_unique<ValueItem>("Shutter", controller->shutter, functionMenu.get(), parentWidget));
    functionMenu->addItem(std::make_unique<ValueItem>("Iris", controller->iris, functionMenu.get(), parentWidget));
    functionMenu->addItem(std::make_unique<ValueItem>("Gain", controller->gain, functionMenu.get(), parentWidget));

    return functionMenu;
}

std::unique_ptr<SubmenuItem> MenuBuilder::buildStream(SubmenuItem* parentMenu, QWidget* parentWidget, Controller* controller)
{
    auto streamMenu = std::make_unique<SubmenuItem>("Stream", parentMenu, parentWidget);

    streamMenu->addItem(std::make_unique<ValueItem>("Display", controller->hdmi_stream, streamMenu.get(), parentWidget));
    streamMenu->addItem(std::make_unique<ValueItem>("RTP", controller->rtp_stream, streamMenu.get(), parentWidget));
    streamMenu->addItem(std::make_unique<ValueItem>("File", controller->file_stream, streamMenu.get(), parentWidget));

    return streamMenu;
}

std::unique_ptr<SubmenuItem> MenuBuilder::buildAdvanced(SubmenuItem* parentMenu, QWidget* parentWidget, Controller*)
{
    auto advMenu = std::make_unique<SubmenuItem>("Advanced", parentMenu, parentWidget);

    // NOTE remove these dangling pointers
    ControlableWidget* widget = new ControlableWidget("...", parentWidget);

    advMenu->addItem(std::make_unique<PopupItem>("test", widget, advMenu.get(), parentWidget));
    advMenu->addItem(std::make_unique<PopupItem>("test 2", widget, advMenu.get(), parentWidget));

    return advMenu;
}
