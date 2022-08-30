#include "menu.h"
#include "global/logcategories.h"
#include "items/valueItem.h"

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
    m_root = std::make_unique<SubmenuItem>(QString{}, m_root.get(), this);

    m_layout = new QVBoxLayout(this);
    m_layout->setAlignment(Qt::AlignTop);
    setPalette(Style::getInstance().menu.main);

    MenuBuilder::buildMenuTree(m_root.get(), this);
}

void Menu::keyPressEvent(QKeyEvent *event)
{
    switch (m_currentMode)
    {
    case INACTIVE:
        if (event->key() == Qt::Key_Right)
        {
            open();
        }
        break;

    case ACTIVE:
        menuNav(event);
        break;

    case EXEC:
        m_currentSubmenu->itemList[m_currentElement]->control(event);
        break;
    }
}

void Menu::startExec()
{
    m_currentMode = EXEC;
}

void Menu::completeExec()
{
    m_currentMode = ACTIVE;

    std::size_t index = m_indexstack.top();
    m_indexstack.pop();

    if (m_currentSubmenu != nullptr)
    {
        setSubmenu(m_currentSubmenu, index);
    }
}

void Menu::menuNav(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Left:
        m_currentSubmenu->itemList[m_currentElement]->setPalette(Style::getInstance().menu.item);

        if (m_currentSubmenu->parentMenu != nullptr)
        {
            std::size_t index = m_indexstack.top();
            m_indexstack.pop();
            setSubmenu(m_currentSubmenu->parentMenu, index);
        }
        else
        {
            close();
        }

        break;

    case Qt::Key_Right:            
        m_indexstack.push(m_currentElement);
        m_currentSubmenu->itemList[m_currentElement]->deselect();
        m_currentSubmenu->itemList[m_currentElement]->execute();
        break;

    case Qt::Key_Up:
        m_currentSubmenu->itemList[m_currentElement]->deselect();

        m_currentElement = m_currentElement == 0? m_currentSubmenu->itemList.size() : m_currentElement;
        --m_currentElement;

        m_currentSubmenu->itemList[m_currentElement]->select();
        break;

    case Qt::Key_Down:
        m_currentSubmenu->itemList[m_currentElement]->deselect();

        ++m_currentElement %= m_currentSubmenu->itemList.size();

        m_currentSubmenu->itemList[m_currentElement]->select();
        break;
    }
}

void Menu::setSubmenu(SubmenuItem *submenu, std::size_t index)
{
    // TODO solve empty list + not display submenu

    if (m_currentSubmenu != nullptr)
    {
        for (auto &&item : m_currentSubmenu->itemList)
        {
            item->setVisible(false);
            m_layout->removeWidget(item.get());
        }
    }

    m_currentSubmenu = submenu;

    for (auto &&item : m_currentSubmenu->itemList)
    {
        item->setVisible(true);
        m_layout->addWidget(item.get());
    }

    m_currentElement = index;
    m_currentSubmenu->itemList[m_currentElement]->select();
}

void Menu::open()
{
    m_currentMode = ACTIVE;
    setSubmenu(m_root.get());
}

void Menu::close()
{
    m_currentMode = INACTIVE;

    for (auto &&item : m_currentSubmenu->itemList)
    {
        item->setVisible(false);
    }
}
