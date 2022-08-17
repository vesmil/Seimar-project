#ifndef VALUEITEM_H
#define VALUEITEM_H

#include "itemBase.h"

#include <QLabel>

class ValueItem : public ItemBase
{
public:
    ValueItem(QWidget* parent);

    void execute() override;

private:
    QLabel *text;
    QLabel *value;
};

#endif // VALUEITEM_H
