#include "valueItem.h"

#include <QHBoxLayout>

ValueItem::ValueItem(QWidget* parent) : ItemBase(parent)
{
    // TODO do I really need a whole layout for one button? - I guess inheritance would be better

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);

    button = new Button();
    button->setText("...");
    button->setVisible(true);
    layout->addWidget(button);

    setter = new valueSetter();
    layout->addWidget(setter);
}
