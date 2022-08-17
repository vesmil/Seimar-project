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
    static void setSubmenu(SubmenuItem* submenu, std::size_t index = 0);

private:
    void open();
    void close();

    enum Mode { INACTIVE, ACTIVE, EXEC } m_currentMode;

    static QVBoxLayout *layout;
    static SubmenuItem *currentSubmenu;

    static std::size_t currentElement;

    std::unique_ptr<SubmenuItem> m_root;
};

#endif // MENU_H
