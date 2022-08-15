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

    void keyPressEvent(QKeyEvent *event);

private:
    void open();
    void close();

    MenuDisplay display;
    std::unique_ptr<SubmenuElement> root;

    bool menuActive;
};

#endif // MENU_H
