#ifndef VALUEITEM_H
#define VALUEITEM_H

#include "itemBase.h"

class ValueItem : public ItemBase
{
public:
    ValueItem(QWidget* parent);

private:
    // text part - button I guess
    // value part - text, arrows, slider, ... (will have custom class I guess)
};

#endif // VALUEITEM_H
