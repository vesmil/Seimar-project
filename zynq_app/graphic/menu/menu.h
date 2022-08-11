#ifndef MENU_H
#define MENU_H

#include <QKeyEvent>
#include <QObject>

#include "Elements/menuElementBase.h"
#include "Elements/submenu.h"

class Menu
{
public:
    Menu();

private:
    Submenu* root;  // mby shared pointers...
    Submenu* currentSubmenu;
    MenuElementBase* selectedElement;  // mby just index

    void keyPressEvent(QKeyEvent *event);

    void open();
    void close();

    void display(); // display all elements in list of current submenu

    // ...
};

#endif // MENU_H
