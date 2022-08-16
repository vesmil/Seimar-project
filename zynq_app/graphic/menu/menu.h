#ifndef MENU_H
#define MENU_H

#include <QKeyEvent>
#include <QObject>
#include <QPushButton>
#include <QVBoxLayout>

#include "items/itemBase.h"
#include "items/submenuitem.h"

/*!
 * \brief
 */

// TODO remake completely as a singleton
class Menu  : public QWidget
{
    Q_OBJECT

public:
    Menu(QWidget *parent = nullptr);

    void keyPressEvent(QKeyEvent *event);
    static void setSubmenu(SubmenuItem* submenu);

private:
    void open();
    void close();

    static QVBoxLayout *layout;
    static SubmenuItem *currentSubmenu;

    // ItemBase *firstElement;
    static int currentElement;

    std::unique_ptr<SubmenuItem> root;

    bool menuActive;
};

#endif // MENU_H
