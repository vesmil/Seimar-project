#ifndef MENU_H
#define MENU_H

#include <QKeyEvent>
#include <QObject>

#include "Elements/elementBase.h"
#include "Elements/submenuElement.h"

class Menu
{
public:
    Menu();

private:
    // To store the structure
    SubmenuElement* root;  // mby shared pointers...

    // To get the element list which will be displayed
    SubmenuElement* currentSubmenu;

    // To execute action and highlight selected
    elementBase* selectedElement;  // mby just index

    void keyPressEvent(QKeyEvent *event);

    void open();
    void close();

    void display(); // display all elements in list of current submenu

    // ...
};

#endif // MENU_H
