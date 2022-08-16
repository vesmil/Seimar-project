#include "submenuElement.h"

#include <QHBoxLayout>
#include "../menu.h"

#include "global/logCategories.h"

SubmenuElement::SubmenuElement(QString text, SubmenuElement *parentMenu, QWidget *parent)
    : ElementBase(parent), parentMenu(parentMenu)
{
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);

    button = new QPushButton(this);
    button->setText(text);
    button->setVisible(true);

    // TODO solve not using mouse...
    connect(button, &QPushButton::released, this, &SubmenuElement::execute);

    layout->addWidget(button);
}

SubmenuElement::~SubmenuElement()
{
}

void SubmenuElement::execute()
{
    qCInfo(uiLog()) << "execute";
    Menu::setSubmenu(this);
}

// execute will set the current menu in display as this submenu
