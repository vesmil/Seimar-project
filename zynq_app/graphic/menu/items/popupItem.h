#ifndef POPUPITEM_H
#define POPUPITEM_H

#include "itemBase.h"

//! \brief Item which will open a new window upon confirmation
class PopupItem : public ItemBase
{
public:
    PopupItem(QWidget* parent);

    void execute() override;
};

#endif // POPUPITEM_H
