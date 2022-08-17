#ifndef MENU_H
#define MENU_H

#include <QKeyEvent>
#include <QObject>
#include <QPushButton>
#include <QVBoxLayout>
#include <stack>

#include "items/itemBase.h"
#include "items/submenuitem.h"

/*!
 * \brief QWidget used to display, control and store the whole menu
 */
class Menu  : public QWidget
{
    Q_OBJECT

public:
    // TODO undo singleton structure
    Menu(QWidget *parent = nullptr);

    void keyPressEvent(QKeyEvent *event);

    enum ControlMode { INACTIVE, ACTIVE, EXEC };
    static void setMode(ControlMode mode); // for valueItem to block interacting with menu - ugly solution so far
    static void setSubmenu(SubmenuItem* submenu, std::size_t index = 0);

private:
    static void open();
    static void close();

    static void menuNav(QKeyEvent *event);

    //! \brief Layout used to store all menu butons (they are added and removed)
    static QVBoxLayout *m_layout;

    //! \brief Stores the whole menu in tree structure - child elements are in elementlist
    static std::unique_ptr<SubmenuItem> m_root;

    static ControlMode m_currentMode;

    //! \brief Submenu from which the elements are displayed
    static SubmenuItem *m_currentSubmenu;

    //! \brief stack used to remember prev indexes when going back
    static std::stack<std::size_t> m_indexstack; // TODO Is this a good solution to remember prev index in menu? Subtracting object pointer from first element in parent could be...
    static std::size_t m_currentElement;


};

#endif // MENU_H
