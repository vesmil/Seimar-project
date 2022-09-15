#ifndef POPUPITEM_H
#define POPUPITEM_H

#include <QKeyEvent>
#include "itembase.h"

// TODO complete popup item

//! \brief Item which will open a new window upon confirmation
class PopupItem : public ItemBase
{
public:
    PopupItem(const QString& text, QWidget* popup, QWidget* parent);

    void executeSelected() override;
    void control(QKeyEvent* event) override;

    // TODO create interface for controlable widget
    QWidget* m_popupWidget;
};

#endif // POPUPITEM_H
