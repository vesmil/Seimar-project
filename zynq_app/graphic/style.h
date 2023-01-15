#ifndef STYLE_H
#define STYLE_H

#include <QString>
#include <QPalette>

//! \brief Singleton used to store cascade styles as QString
class Style
{
public:
    static Style& getInstance();

    struct {
        QString main = "background : gray;"
                       "color : black;";

        QString item = "background : gray;"
                       "color : black;"
                       "padding: 10px;";

        QString selectedItem = "background : rgb(100, 100, 100);"
                               "color : white;"
                               "padding: 10px;";

        QString executedItem = "background : rgb(220,130,0);"
                               "color : white;"
                               "padding: 10px;";

        QString emptyItemList = "background : rgb(80,10,10);"
                                "color : white;"
                                "padding: 10px;";

        QString hiddenItem = "background : gray;"
                             "color : rgb(90,90,90);"
                             "padding: 10px;";
    } menu;

private:
    Style();

    Style (const Style&) = delete;
    Style& operator= (const Style&) = delete;
};

#endif // STYLE_H
