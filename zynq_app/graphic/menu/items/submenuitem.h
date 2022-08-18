#ifndef SUBMENUITEM_H
#define SUBMENUITEM_H

#include <vector>
#include <memory>
#include <qpushbutton.h>
#include <QLabel>

#include "itemBase.h"

//! \brief Menu element from which next menu will be opened
class SubmenuItem : public ItemBase
{
public:
    SubmenuItem(QString text, SubmenuItem *parentMenu, QWidget *parent = nullptr);

    void execute() override;

    QLabel* m_text;

    SubmenuItem* parentMenu;
    std::vector<std::unique_ptr<ItemBase>> itemList{};
};

#endif // SUBMENUITEM_H
