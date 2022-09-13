#include "menu.h"
#include "global/logcategories.h"
#include "items/valueitem.h"

#include "global/logcategories.h"
#include "graphic/style.h"
#include "menubuilder.h"

Menu& Menu::getInstance()
{
    static Menu instance;
    return instance;
}

Menu::Menu() : QWidget()
{
    m_root = std::make_unique<SubmenuItem>(QString{}, nullptr, this);

    new QVBoxLayout(this);  
    layout()->setAlignment(Qt::AlignTop);
    setStyleSheet(Style::getInstance().menu.main);
}

void Menu::keyPressEvent(QKeyEvent *event)
{
    if (m_active)
    {
        m_currentItem->control(event);
    }
    else if (event->key() == Qt::Key_Right)
    {
        open();
    }
}

void Menu::setSubmenu(SubmenuItem* submenu)
{
    m_currentItem = submenu;
}

SubmenuItem* Menu::getRoot()
{
    return m_root.get();
}

void Menu::open()
{
    m_active = true;

    m_currentItem = m_root.get();
    m_currentItem->open();
}

void Menu::exit()
{
    m_active = false;

    m_currentItem->exit();
}
