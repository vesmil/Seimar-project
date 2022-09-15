#include "popupitem.h"

#include <QLabel>
#include <graphic/menu/menu.h>

PopupItem::PopupItem(const QString& text, ControlableWidget* popupWidget, SubmenuItem* parentMenu, QWidget* parent): ItemBase(parent, parentMenu), m_popupWidget(popupWidget)
{
    new ItemLayout(this);
    QLabel* label = new QLabel(this);
    label->setText(text);
    layout()->addWidget(label);
    m_popupWidget->setVisible(false);
}

void PopupItem::execute()
{
    layout()->addWidget(m_popupWidget);
    m_popupWidget->setVisible(true);
    ItemBase::execute();
}

void PopupItem::control(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Left)
    {
        layout()->removeWidget(m_popupWidget);
        m_popupWidget->setVisible(false);

        Menu::getInstance().setOnSubmenu(m_parentMenu);
    }
    else
    {
        m_popupWidget->control(event);
    }
}
