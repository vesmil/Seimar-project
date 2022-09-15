#ifndef POPUPITEM_H
#define POPUPITEM_H

#include <QKeyEvent>

#include "library/controller/popup.h"
#include "itembase.h"

//! \brief Item which will open a new window upon confirmation
class PopupItem : public ItemBase
{
public:
    PopupItem(const QString& text, ControlableWidget* popup, SubmenuItem* parentMenu, QWidget* parent);

    void executeSelected() override;
    void control(QKeyEvent* event) override;

    ControlableWidget* m_popupWidget;
};

#endif // POPUPITEM_H
