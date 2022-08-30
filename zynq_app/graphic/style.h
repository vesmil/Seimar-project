#ifndef STYLE_H
#define STYLE_H

#include <QString>

#include <QPalette>

// TODO QPlaette vs QML vs Style sheets

class Style
{
public:
    static Style& getInstance();

    /* struct {
        QString main = "background-color : gray; color : black;";

        QString item = "background-color : gray; color : black;";
        QString selectedItem = "background-color : darkgray; color : white;";
        QString executedItem = "background-color : cyan; color : black;";
    } menu; */

    struct {
        QPalette main;

        QPalette item;
        QPalette selectedItem;
        QPalette executedItem;
    } menu;

private:

    Style();
};

#endif // STYLE_H
