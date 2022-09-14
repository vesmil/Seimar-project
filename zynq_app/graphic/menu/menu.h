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

    void completeExec();

    // TODO move the responsibilities of SubmenuItem out of Menu -> remove ControlMode and Exec

    // backToParent(SubmenuItem ...)
    // gotoChild(ItemBase ...)
    //

    void setSubmenu(SubmenuItem* submenu);

    void refreshMenu();

    SubmenuItem* getRoot();

    ItemBase *m_currentItem = nullptr;

    void open();
    void close();

private:
    Menu();

    //! \brief Stores the whole menu in tree structure - child elements are in elementlist
    std::unique_ptr<SubmenuItem> m_root = nullptr;

    //! \brief Submenu from which the elements are displayed
    SubmenuItem *m_currentSubmenu = nullptr;

    bool m_active;
    bool m_controlToItem;
};

#endif // MENU_H
