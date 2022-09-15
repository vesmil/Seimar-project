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

    void open();
    void close();

    void keyPressEvent(QKeyEvent *event);

    void setCurrentItem(ItemBase* item);
    void setOnSubmenu(SubmenuItem* submenu);

    SubmenuItem* getRoot();

private:
    Menu();
    bool m_active;

    //! \brief Stores the whole menu in tree structure - child elements are in elementlist
    std::unique_ptr<SubmenuItem> m_root = nullptr;

    //! \brief Item in charge of menu controls
    ItemBase *m_currentItem = nullptr;

    //! \brief Submenu from which the elements are displayed
    SubmenuItem *m_currentSubmenu = nullptr;
};

#endif // MENU_H
