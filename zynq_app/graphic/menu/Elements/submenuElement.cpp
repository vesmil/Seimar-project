#include "submenuElement.h"

#include <QHBoxLayout>

SubmenuElement::SubmenuElement(QString text, SubmenuElement *parentMenu, QWidget *parent)
    : ElementBase(parent), parentMenu(parentMenu)
{
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);

    button = new QPushButton(this);
    button->setText(text);
    button->setVisible(true);

    layout->addWidget(button);
}

SubmenuElement::~SubmenuElement()
{
}

void SubmenuElement::execute()
{

}

// execute will set the current menu in display as this submenu
