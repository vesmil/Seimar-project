#include "menubuilder.h"

void MenuBuilder::buildMenuTree(SubmenuItem* root, QWidget* parent)
{
    for (int i = 0; i < 5; i++)
    {
        root->itemList.emplace_back(std::make_unique<SubmenuItem>(QString::number(i), root, parent));

        for (int j = 0; j < 6; j++)
        {
            SubmenuItem* casted = static_cast<SubmenuItem*>((root->itemList[i]).get());

            int* val = new int(0);  // obvs the values will be stored elswhere
            casted->itemList.emplace_back(std::make_unique<ValueItem<int>>(QString::number(i) + QString::number(j), *val, parent));
        }
    }

    root->itemList.emplace_back(std::make_unique<PopupItem>(parent));
}
