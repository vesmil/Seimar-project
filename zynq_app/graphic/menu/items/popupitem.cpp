#include "popupitem.h"

#include <QLabel>
#include <graphic/menu/menu.h>

PopupItem::PopupItem(const QString& text, QWidget* popupWidget, QWidget* parent): ItemBase(parent), m_popupWidget(popupWidget)
{
    new ItemLayout(this);
    QLabel* label = new QLabel(this);
    label->setText(text);
    layout()->addWidget(label);

    // m_popupWidget->setVisible(false);
}

void PopupItem::executeSelected()
{
    layout()->addWidget(m_popupWidget);
    m_popupWidget->setVisible(true);
    ItemBase::executeSelected();
}

void PopupItem::control(QKeyEvent* event)
{
    switch (event->key())
    {
    case Qt::Key_Left:
        layout()->removeWidget(m_popupWidget);
        m_popupWidget->setVisible(false);

        Menu::getInstance().completeExec();
        break;

    case Qt::Key_Right:
        layout()->removeWidget(m_popupWidget);
        m_popupWidget->setVisible(false);

        Menu::getInstance().completeExec();
        break;

    case Qt::Key_Up:
    {
        break;
    }

    case Qt::Key_Down:
        break;
    }
}
