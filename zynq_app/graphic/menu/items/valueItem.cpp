#include "valueItem.h"

#include <QHBoxLayout>
#include "../itemlayout.h"

ValueItem::ValueItem(QWidget* parent) : ItemBase(parent)
{
    ItemLayout* layout = new ItemLayout(this);

    text = new QLabel();
    text->setText("..."); // TODO
    layout->addWidget(text);

    value = new QLabel();
    value->setText("0"); // TODO
    layout->addWidget(value);
}

void ValueItem::execute()
{
    // TODO set menu to EXEC mode - to get all the input
}
