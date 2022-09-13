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

    enum ControlMode { INACTIVE, ACTIVE, EXEC };

    void startExec();
    void completeExec();

    void setSubmenu(SubmenuItem* submenu, std::size_t index = 0);

    //! \brief Stores the whole menu in tree structure - child elements are in elementlist
    std::unique_ptr<SubmenuItem> m_root = nullptr;
    // TODO private

private:
    Menu();

    void open();
    void close();

    void menuNav(QKeyEvent *event);

    ControlMode m_currentMode = INACTIVE;

    //! \brief Submenu from which the elements are displayed
    SubmenuItem *m_currentSubmenu = nullptr;

    //! \brief stack used to remember prev indexes when going back
    std::stack<std::size_t> m_indexstack{};
    std::size_t m_currentElement = 0;
};

#endif // MENU_H
