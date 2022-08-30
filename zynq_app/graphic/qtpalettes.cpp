#include "qtpalettes.h"

QtPalettes& QtPalettes::getInstance()
{
    static QtPalettes instance;
    return instance;
}

QtPalettes::QtPalettes()
{
    menu.main.setColor(QPalette::Window, Qt::gray);

    menu.item.setColor(QPalette::Window, Qt::gray);
    menu.selectedItem.setColor(QPalette::Window, Qt::darkGray);
    menu.executedItem.setColor(QPalette::Window, Qt::cyan);

}
