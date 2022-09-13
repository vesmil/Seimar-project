#ifndef MENU_H
#define MENU_H

#include <QKeyEvent>
#include <QVBoxLayout>
#include <stack>

#include "graphic/menu/items/itembase.h"
#include "graphic/menu/items/submenuitem.h"

/*!
 * \brief QWidget used to display, control and store the whole menu
 */
class Menu  : public QWidget
{
    Q_OBJECT

public:
    static Menu& getInstance();

    void keyPressEvent(QKeyEvent *event);
    void setSubmenu(SubmenuItem* submenu);

    SubmenuItem *getRoot();

    void open();
    void exit();

private:
    Menu();

    //! \brief Stores the whole menu in tree structure - child elements are in elementlist
    std::unique_ptr<SubmenuItem> m_root = nullptr;
    ItemBase *m_currentItem = nullptr;

    bool m_active = false;
};

#endif // MENU_H
