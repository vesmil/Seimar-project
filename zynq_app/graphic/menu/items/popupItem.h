#ifndef POPUPITEM_H
#define POPUPITEM_H

#include "itemBase.h"

class PopupItem : public ItemBase
{
public:
    PopupItem(QWidget* parent);

    void execute() override;
};

#endif // POPUPITEM_H
