#include "menubuilder.h"

#include "library/application/settings.h"
#include "library/controller/controller.h"

void MenuBuilder::buildMenuTree(SubmenuItem* root, QWidget* parent, Controller* controller)
{
    root->itemList.emplace_back(std::make_unique<SubmenuItem>("Functions", root, parent));
    root->itemList.emplace_back(std::make_unique<SubmenuItem>("Stream", root, parent));
    root->itemList.emplace_back(std::make_unique<SubmenuItem>("Advanced", root, parent));

    SubmenuItem* casted = static_cast<SubmenuItem*>((root->itemList[0]).get());

    Value<int, Controller>* zoom_val = new Value<int, Controller>{Settings::getInstance().visca.zoom, &Controller::setZoom, controller};
    casted->itemList.emplace_back(std::make_unique<ValueItem>("Zoom", *zoom_val, parent));

    // Value<uint16_t, Controller>* exp_val = new Value<uint16_t, Controller>{Settings::getInstance().visca.zoom, &Controller::setZoom, controller};
    // casted->itemList.emplace_back(std::make_unique<ValueItem>("Exposure", *zoom_val, parent));

    //casted->itemList.emplace_back(std::make_unique<ValueItem<int>>("Exposure", *val, parent));

    SubmenuItem* casted2 = static_cast<SubmenuItem*>((root->itemList[1]).get());
    //casted2->itemList.emplace_back(std::make_unique<ValueItem<int>>("Display", *val, parent));
    //casted2->itemList.emplace_back(std::make_unique<ValueItem<int>>("RTP", *val, parent));
    //casted2->itemList.emplace_back(std::make_unique<ValueItem<int>>("File", *val, parent));

    SubmenuItem* casted3 = static_cast<SubmenuItem*>((root->itemList[2]).get());
    casted3->itemList.emplace_back(std::make_unique<PopupItem>(parent));
}
