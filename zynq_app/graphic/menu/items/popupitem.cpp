#include "popupitem.h"

#include <QLabel>
#include <graphic/menu/menu.h>

PopupItem::PopupItem(const QString& text, IControlablePopup* popupWidget, SubmenuItem* parentMenu, QWidget* parent): ItemBase(parent, parentMenu), m_popupWidget(popupWidget)
{
    new ItemLayout(this);
    QLabel* label = new QLabel(this);
    label->setText(text);
    layout()->addWidget(label);
    // m_popupWidget->setVisible(false);
}

void PopupItem::execute()
{
    layout()->addWidget(m_popupWidget->getWidget());
    m_popupWidget->open();
    ItemBase::execute();
}

void PopupItem::control(QKeyEvent* event)
{
    m_popupWidget->control(event);

    if (event->key() == Qt::Key_Left || event->key() == Qt::Key_Right)
    {
        // layout()->removeWidget(m_popupWidget);
        // m_popupWidget->setVisible(false);

        Menu::getInstance().setOnSubmenu(m_parentMenu);
    }
}
