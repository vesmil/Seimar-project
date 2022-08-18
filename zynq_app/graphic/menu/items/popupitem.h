#ifndef POPUPITEM_H
#define POPUPITEM_H

#include "itembase.h"

#include <QKeyEvent>

//! \brief Item which will open a new window upon confirmation
class PopupItem : public ItemBase
{
public:
    PopupItem(QWidget* parent);

    void execute() override;

    void control(QKeyEvent* event) override;
};

#endif // POPUPITEM_H
