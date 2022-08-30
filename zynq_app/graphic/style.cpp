#include "style.h"

Style& Style::getInstance()
{
    static Style instance;
    return instance;
}

Style::Style()
{
    menu.main.setColor(QPalette::Window, Qt::gray);

    menu.item.setColor(QPalette::Window, Qt::gray);
    menu.selectedItem.setColor(QPalette::Window, Qt::darkGray);
    menu.executedItem.setColor(QPalette::Window, QColor(220,130,0));
}
