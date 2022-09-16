#include "menu.h"

#include "graphic/style.h"

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

void Menu::setCurrentItem(ItemBase* item)
{
    m_currentItem = item;
}

void Menu::setOnSubmenu(SubmenuItem *submenu)
{
    if (m_currentSubmenu)
    {
        m_currentSubmenu->close(layout());
    }

    m_currentItem = m_currentSubmenu = submenu;
    submenu->display(layout());
}

SubmenuItem* Menu::getRoot()
{
    return m_root.get();
}

void Menu::open()
{
    m_active = true;
    setOnSubmenu(m_root.get());
}

void Menu::close()
{
    m_active = false;
    m_currentSubmenu->close(layout());
}
