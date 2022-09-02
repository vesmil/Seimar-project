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
        m_currentSubmenu->itemList[m_currentElement]->setStyleSheet(Style::getInstance().menu.item);

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
    // TDOO don't display empty submenu?
    if (submenu->itemList.size() == 0)
    {
        m_currentSubmenu->itemList[m_currentElement]->select();
        m_currentSubmenu->itemList[m_currentElement]->setStyleSheet(Style::getInstance().menu.emptyItemList);
        qCWarning(uiLog()) << "Empty submenu";
        return;
    }

    if (m_currentSubmenu != nullptr)
    {
        for (auto &&item : m_currentSubmenu->itemList)
        {
            item->setVisible(false);
            layout()->removeWidget(item.get());
        }
    }

    m_currentSubmenu = submenu;

    for (auto &&item : m_currentSubmenu->itemList)
    {
        if (!item->isHidden())
        {
            item->setVisible(true);
            layout()->addWidget(item.get());
        }
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
