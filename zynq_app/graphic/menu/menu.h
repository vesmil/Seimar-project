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

    //! \brief Displays the menu on the screen and starts receiving key events
    void open();
    //! \brief Hides the menu and stops receiving key events
    void close();

    void keyPressEvent(QKeyEvent *event);

    //! \brief Set the current item to \a item
    void setCurrentItem(ItemBase* item);

    //! \brief Closes current submenu, sets and opens \a submenu
    void setOnSubmenu(SubmenuItem* submenu);

    //! \brief Returns pointer to the root of the menu
    //! \note Without menu, the pointer is not valid
    SubmenuItem* getRoot();

private:
    Menu();
    bool m_active = false;

    //! \brief Stores the whole menu in treelike structure
    std::unique_ptr<SubmenuItem> m_root = nullptr;

    //! \brief Item in charge of menu controls
    ItemBase *m_currentItem = nullptr;
    //! \brief Submenu from which the elements are displayed
    SubmenuItem *m_currentSubmenu = nullptr;
};

#endif // MENU_H
