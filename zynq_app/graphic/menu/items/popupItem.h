#ifndef POPUPITEM_H
#define POPUPITEM_H

#include "itemBase.h"

class PopupItem : public ItemBase
{
public:
    PopupItem(QWidget* parent);

    void execute();
};

#endif // POPUPITEM_H
