#ifndef QTPALETTES_H
#define QTPALETTES_H

#include <QPalette>

// TODO QPlaette vs QML vs Style sheets

class QtPalettes
{
public:
    static QtPalettes& getInstance();

    struct {
        QPalette main;

        QPalette item;
        QPalette selectedItem;
        QPalette executedItem;
    } menu;

private:

    QtPalettes();
};

#endif // QTPALETTES_H
