#include "popupitem.h"

#include <QLabel>

#include <graphic/menu/itemlayout.h>
#include <graphic/menu/menu.h>

PopupItem::PopupItem(QWidget* parent) : ItemBase(parent)
{
    ItemLayout* layout = new ItemLayout(this);

    QLabel* label = new QLabel(this);
    label->setText("5");

    layout->addWidget(label);
}

void PopupItem::execute()
{
    ItemBase::execute();
    Menu::getInstance().startExec();
}

void PopupItem::control(QKeyEvent* event)
{
    switch (event->key())
    {
    case Qt::Key_Left:
        Menu::getInstance().completeExec();
        break;

    case Qt::Key_Right:
        Menu::getInstance().completeExec();
        break;

    case Qt::Key_Up:
    {
        QLabel* label = new QLabel(this);
        label->setText("...");
        layout()->addWidget(label);
     }
        break;

    case Qt::Key_Down:
        layout()->removeItem(layout()->takeAt(0));
        break;
    }
}
