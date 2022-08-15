#ifndef MENU_H
#define MENU_H

#include <QKeyEvent>
#include <QObject>
#include <QPushButton>

#include "Elements/elementBase.h"
#include "Elements/submenuElement.h"

/*!
 * \brief Logic behind menu - holding the structure and processing inputs
 */
class Menu  : public QWidget
{
    Q_OBJECT

public:
    Menu(QWidget *parent = nullptr);

    void keyPressEvent(QKeyEvent *event);

private:
    void open();
    void close();

    SubmenuElement *currentSubmenu;
    ElementBase *selectedElement;

    std::unique_ptr<SubmenuElement> root;

    bool menuActive;
};

#endif // MENU_H
