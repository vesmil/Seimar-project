#include "submenuitem.h"

#include <QHBoxLayout>
#include "../menu.h"

#include "global/logCategories.h"

SubmenuItem::SubmenuItem(QString text, SubmenuItem *parentMenu, QWidget *parent)
    : ItemBase(parent), parentMenu(parentMenu)
{
    // TODO do I really need a whole layout for one button?
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);

    button = new Button();
    button->setText(text);
    button->setVisible(true);

    // TODO I dont need that as it won't be a button
    // connect(button, &QPushButton::released, this, &SubmenuItem::execute);

    layout->addWidget(button);
}

void SubmenuItem::execute()
{
    qCInfo(uiLog()) << "execute";
    Menu::setSubmenu(this);
}

// execute will set the current menu in display as this submenu
