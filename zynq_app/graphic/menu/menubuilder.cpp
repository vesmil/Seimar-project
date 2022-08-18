#include "menubuilder.h"

void MenuBuilder::buildRoot(SubmenuItem* root, QWidget* parent)
{
    for (int i = 0; i < 5; i++)
    {
        root->itemList.emplace_back(std::make_unique<SubmenuItem>(QString::number(i), root, parent));
        root->itemList[i]->setVisible(false);

        for (int j = 0; j < 6; j++)
        {
            SubmenuItem* casted = static_cast<SubmenuItem*>((root->itemList[i]).get());
            casted->itemList.emplace_back(std::make_unique<SubmenuItem>(QString::number(i) + QString::number(j), casted, parent));
            casted->itemList[j]->setVisible(false);

            for (int k = 0; k < 10; k++)
            {
                SubmenuItem* casted2 = static_cast<SubmenuItem*>((casted->itemList[j]).get());

                int* val = new int(0);  // obvs the values will be stored elswhere
                casted2->itemList.emplace_back(std::make_unique<ValueItem<int>>(QString::number(i) + QString::number(j) + QString::number(k), *val, parent));
                casted2->itemList[k]->setVisible(false);
            }
        }
    }

    root->itemList.emplace_back(std::make_unique<PopupItem>(parent));
    root->itemList[5]->setVisible(false);
}
