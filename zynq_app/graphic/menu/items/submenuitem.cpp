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

void SubmenuItem::execute()
{
    m_currentElement = 0;
    Menu::getInstance().setOnSubmenu(this);
}

void SubmenuItem::control(QKeyEvent* event)
{
    switch (event->key())
    {
        case Qt::Key_Left:
            goBack();
            break;

        case Qt::Key_Right:
            Menu::getInstance().setCurrentItem(m_itemList[m_currentElement].get());
            m_itemList[m_currentElement]->onDeselect();
            m_itemList[m_currentElement]->execute();
            break;

        case Qt::Key_Up:
            moveUp();
            break;

        case Qt::Key_Down:
            moveDown();
            break;
    }
}

void SubmenuItem::goBack()
{
    m_itemList[m_currentElement]->setStyleSheet(Style::getInstance().menu.item);

    if (m_parentMenu != nullptr)
    {
        Menu::getInstance().setOnSubmenu(m_parentMenu);
    }
    else
    {
        Menu::getInstance().close();
    }
}

void SubmenuItem::moveUp()
{
    m_itemList[m_currentElement]->onDeselect();

    // NOTE prob could find next not hidden item better way...
    do
    {
        m_currentElement = m_currentElement == 0? m_itemList.size() : m_currentElement;
        --m_currentElement;
    }
    while (m_itemList[m_currentElement]->isHidden());

    m_itemList[m_currentElement]->onSelect();
}

void SubmenuItem::moveDown()
{
    m_itemList[m_currentElement]->onDeselect();

    do
    {
            ++m_currentElement %= m_itemList.size();
    }
    while (m_itemList[m_currentElement]->isHidden());

    m_itemList[m_currentElement]->onSelect();
}

bool SubmenuItem::isHidden()
{
    return m_itemList.size() == 0;
}

void SubmenuItem::addItem(std::unique_ptr<ItemBase> item)
{
    m_itemList.emplace_back(std::move(item));
}

void SubmenuItem::display(QLayout* layout)
{
    if( m_itemList.size() == 0)
    {
        qCWarning(uiLog()) << "Empty submenu";
        return;
    }

    for (auto &&item : m_itemList)
    {
        if (!item->isHidden())
        {
            item->setVisible(true);
            layout->addWidget(item.get());
        }
    }

    m_itemList[m_currentElement]->onSelect();
}

void SubmenuItem::close(QLayout* layout)
{
    for (auto &&item : m_itemList)
    {
        item->setVisible(false);
        layout->removeWidget(item.get());
    }
}
