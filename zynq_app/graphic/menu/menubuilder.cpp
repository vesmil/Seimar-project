#include "menubuilder.h"

void MenuBuilder::buildMenuTree(SubmenuItem* root, QWidget* parent)
{
    root->itemList.emplace_back(std::make_unique<SubmenuItem>("Functions", root, parent));
    root->itemList.emplace_back(std::make_unique<SubmenuItem>("Stream", root, parent));
    root->itemList.emplace_back(std::make_unique<SubmenuItem>("Advanced", root, parent));

    SubmenuItem* casted = static_cast<SubmenuItem*>((root->itemList[0]).get());
    int* val = new int(0);
    casted->itemList.emplace_back(std::make_unique<ValueItem<int>>("...", *val, parent));

    int* val2 = new int(0);
    casted->itemList.emplace_back(std::make_unique<ValueItem<int>>("...", *val2, parent));

    SubmenuItem* casted2 = static_cast<SubmenuItem*>((root->itemList[1]).get());
    casted2->itemList.emplace_back(std::make_unique<PopupItem>(parent));
}
