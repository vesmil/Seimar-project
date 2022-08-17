#ifndef VALUEITEM_H
#define VALUEITEM_H

#include "itemBase.h"
#include "displayElements/button.h"
#include "displayElements/valueSetter.h"

class ValueItem : public ItemBase
{
public:
    ValueItem(QWidget* parent);

private:
    Button *button;
    valueSetter *setter; // TODO connect
};

#endif // VALUEITEM_H
