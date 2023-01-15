#include "menubuilder.h"

#include "library/controller/controller.h"
#include "library/application/settings.h"
#include "graphic/menu/items/valueitem.h"
#include "graphic/menu/items/popupitem.h"

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

    functionMenu->addItem(std::make_unique<ValueItem>("Zoom", controller->zoom.get(), functionMenu.get(), parentWidget, true));

    functionMenu->addItem(std::make_unique<ValueItem>("Focus mode", controller->autofocus.get(), functionMenu.get(), parentWidget, true));
    functionMenu->addItem(std::make_unique<ValueItem>("Focus distance", controller->focusDistance.get(), functionMenu.get(), parentWidget, true));

    functionMenu->addItem(std::make_unique<ValueItem>("Exposure mode", controller->exposureMode.get(), functionMenu.get(), parentWidget));
    functionMenu->addItem(std::make_unique<ValueItem>("Shutter", controller->shutter.get(), functionMenu.get(), parentWidget));
    functionMenu->addItem(std::make_unique<ValueItem>("Iris", controller->iris.get(), functionMenu.get(), parentWidget));
    functionMenu->addItem(std::make_unique<ValueItem>("Gain", controller->gain.get(), functionMenu.get(), parentWidget));

    functionMenu->addItem(std::make_unique<ValueItem>("White balance", controller->whiteBalance.get(), functionMenu.get(), parentWidget));
    functionMenu->addItem(std::make_unique<ValueItem>("R Gain", controller->rGain.get(), functionMenu.get(), parentWidget));
    functionMenu->addItem(std::make_unique<ValueItem>("B Gain", controller->bGain.get(), functionMenu.get(), parentWidget));

    functionMenu->addItem(std::make_unique<ValueItem>("Visibility enhancer", controller->visibilityEnhancer.get(), functionMenu.get(), parentWidget));
    functionMenu->addItem(std::make_unique<ValueItem>("Backlight Compensation", controller->backLight.get(), functionMenu.get(), parentWidget));
    return functionMenu;
}

std::unique_ptr<SubmenuItem> MenuBuilder::buildStream(SubmenuItem* parentMenu, QWidget* parentWidget, Controller* controller)
{
    auto streamMenu = std::make_unique<SubmenuItem>("Stream", parentMenu, parentWidget);

    streamMenu->addItem(std::make_unique<ValueItem>("Display", controller->hdmi_stream.get(), streamMenu.get(), parentWidget));
    streamMenu->addItem(std::make_unique<ValueItem>("RTP", controller->rtp_stream.get(), streamMenu.get(), parentWidget));
    streamMenu->addItem(std::make_unique<ValueItem>("File", controller->file_stream.get(), streamMenu.get(), parentWidget));

    return streamMenu;
}

std::unique_ptr<SubmenuItem> MenuBuilder::buildAdvanced(SubmenuItem* parentMenu, QWidget* parentWidget, Controller* controller)
{
    auto advMenu = std::make_unique<SubmenuItem>("Advanced", parentMenu, parentWidget);

    advMenu->addItem(std::make_unique<ValueItem>("Power", controller->power.get(), advMenu.get(), parentWidget));
    advMenu->addItem(std::make_unique<ValueItem>("Colorspace", controller->colorspace.get(), advMenu.get(), parentWidget));
    advMenu->addItem(std::make_unique<ValueItem>("Format", controller->format.get(), advMenu.get(), parentWidget));

    // advMenu->addItem(std::make_unique<PopupItem>("IP address for RTP", controller->rtpAdress.get(), advMenu.get(), parentWidget));

    return advMenu;
}
