#ifndef MENU_H
#define MENU_H

#include <QKeyEvent>
#include <QObject>
#include <QPushButton>

#include "Elements/elementBase.h"
#include "Elements/submenuElement.h"
#include "menuDisplay.h"

/*!
 * \brief Logic behind menu - holding the structure and processing inputs
 */
class Menu
{
public:
    Menu(QWidget *parent = nullptr);

private:
    std::unique_ptr<SubmenuElement> root;

    void open();
    void keyPressEvent(QKeyEvent *event);

    MenuDisplay display;
    bool menuActive;
};

#endif // MENU_H
