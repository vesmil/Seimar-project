#ifndef POPUPITEM_H
#define POPUPITEM_H

#include <QKeyEvent>
#include "itembase.h"

//! \brief Item which will open a new window upon confirmation
class PopupItem : public ItemBase
{
public:
    PopupItem(QWidget* parent);

    void open() override;
    void exit() override;

    void control(QKeyEvent* event) override;
};

#endif // POPUPITEM_H
