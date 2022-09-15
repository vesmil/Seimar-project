#ifndef MENU_H
#define MENU_H

#include <QKeyEvent>
#include <QVBoxLayout>
#include <stack>

#include "items/itembase.h"
#include "items/submenuitem.h"

/*!
 * \brief QWidget used to display, control and store the whole menu
 */
class Menu  : public QWidget
{
    Q_OBJECT

public:
    static Menu& getInstance();

    void keyPressEvent(QKeyEvent *event);

    void open();
    void close();

    void setItem(ItemBase* item);
    void displaySubmenu(SubmenuItem* submenu);

    SubmenuItem* getRoot();

private:
    Menu();

    //! \brief Stores the whole menu in tree structure - child elements are in elementlist
    std::unique_ptr<SubmenuItem> m_root = nullptr;
    ItemBase *m_currentItem = nullptr;

    //! \brief Submenu from which the elements are displayed
    SubmenuItem *m_currentSubmenu = nullptr;

    bool m_active;
};

#endif // MENU_H
