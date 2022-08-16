#ifndef MENU_H
#define MENU_H

#include <QKeyEvent>
#include <QObject>
#include <QPushButton>
#include <QVBoxLayout>

#include "Elements/elementBase.h"
#include "Elements/submenuElement.h"

/*!
 * \brief
 */

class Menu  : public QWidget
{
    Q_OBJECT

public:
    // TODO remake as singleton

    Menu(QWidget *parent = nullptr);

    void keyPressEvent(QKeyEvent *event);
    static void setSubmenu(SubmenuElement* submenu);

private:
    void open();
    void close();

    static QVBoxLayout* layout;
    static SubmenuElement *currentSubmenu;
    static ElementBase *selectedElement;

    std::unique_ptr<SubmenuElement> root;

    bool menuActive;
};

#endif // MENU_H
