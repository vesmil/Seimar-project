#include "submenuitem.h"

#include "graphic/menu/menu.h"
#include "global/logcategories.h"

#include <graphic/style.h>

// TODO replace singleton refrences with func params

SubmenuItem::SubmenuItem(QString text, SubmenuItem *parentMenu, QWidget *parent)
    : ItemBase(parent, parentMenu)
{
    ItemLayout* layout = new ItemLayout(this);

    m_text = new QLabel(this);
    m_text->setText(text);
    m_text->setVisible(true);

    layout->addWidget(m_text);
}

void SubmenuItem::executeSelected()
{
    m_currentElement = 0;
    Menu::getInstance().displaySubmenu(this);
}

void SubmenuItem::control(QKeyEvent* event)
{
    switch (event->key())
    {
        case Qt::Key_Left:
            goBack();
            break;

        case Qt::Key_Right:
            Menu::getInstance().setItem(itemList[m_currentElement].get());
            itemList[m_currentElement]->onDeselect();
            itemList[m_currentElement]->executeSelected();
            break;

        case Qt::Key_Up:
            moveUp();
            break;

        case Qt::Key_Down:
            moveDown();
            break;
    }
}

void SubmenuItem::close()
{
    // TODO add layout as param

    for (auto &&item : itemList)
    {
        item->setVisible(false);
        Menu::getInstance().layout()->removeWidget(item.get());
    }
}

void SubmenuItem::goBack()
{
    itemList[m_currentElement]->setStyleSheet(Style::getInstance().menu.item);

    if (m_parentMenu != nullptr)
    {
        Menu::getInstance().displaySubmenu(m_parentMenu);
    }
    else
    {
        Menu::getInstance().close();
    }
}

void SubmenuItem::moveUp()
{
    itemList[m_currentElement]->onDeselect();

    // NOTE prob could find next not hidden item better way...

    do
    {
        m_currentElement = m_currentElement == 0? itemList.size() : m_currentElement;
        --m_currentElement;
    }
    while (itemList[m_currentElement]->isHidden());

    itemList[m_currentElement]->onSelect();
}

void SubmenuItem::moveDown()
{
    itemList[m_currentElement]->onDeselect();

    do
    {
            ++m_currentElement %= itemList.size();
    }
    while (itemList[m_currentElement]->isHidden());

    itemList[m_currentElement]->onSelect();
}

bool SubmenuItem::isHidden()
{
    return itemList.size() == 0;
}

void SubmenuItem::display()
{
    // TODO add layout as

    for (auto &&item : itemList)
    {
        if (!item->isHidden())
        {
            item->setVisible(true);
            Menu::getInstance().layout()->addWidget(item.get());
        }
    }

    itemList[m_currentElement]->onSelect();
}
