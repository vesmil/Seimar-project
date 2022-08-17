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
 * \brief
 */

// TODO remake completely as a singleton
class Menu  : public QWidget
{
    Q_OBJECT

public:
    Menu(QWidget *parent = nullptr);

    void keyPressEvent(QKeyEvent *event);

    enum Mode { INACTIVE, ACTIVE, EXEC };
    static void setMode(Mode mode);
    static void setSubmenu(SubmenuItem* submenu, std::size_t index = 0);

private:
    void open();
    void close();

    void menuNav(QKeyEvent *event);

    static QVBoxLayout *m_layout;

    static Mode m_currentMode;
    static SubmenuItem *m_currentSubmenu;
    static std::size_t m_currentElement;

    static std::unique_ptr<SubmenuItem> m_root;

    static std::stack<std::size_t> m_indexstack; // Is this a good solution to remember prev index in menu?
};

#endif // MENU_H
