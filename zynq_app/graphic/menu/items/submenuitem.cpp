#include "submenuitem.h"

#include "graphic/menu/menu.h"
#include "global/logcategories.h"

#include <graphic/style.h>

SubmenuItem::SubmenuItem(QString text, SubmenuItem *parentMenu, QWidget *parent)
    : ItemBase(parent), parentMenu(parentMenu)
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
    Menu::getInstance().setSubmenu(this);
}

void SubmenuItem::control(QKeyEvent* event)
{
    switch (event->key())
    {
        case Qt::Key_Left:
            itemList[m_currentElement]->setStyleSheet(Style::getInstance().menu.item);

            if (parentMenu != nullptr)
            {
                Menu::getInstance().setSubmenu(parentMenu);
            }
            else
            {
                Menu::getInstance().close();
            }

            break;

        case Qt::Key_Right:
            Menu::getInstance().m_currentItem = itemList[m_currentElement].get();

            itemList[m_currentElement]->onDeselect();
            itemList[m_currentElement]->executeSelected();

            break;

        case Qt::Key_Up:
            itemList[m_currentElement]->onDeselect();

            do
            {
                m_currentElement = m_currentElement == 0? itemList.size() : m_currentElement;
                --m_currentElement;
            }
            while (itemList[m_currentElement]->isHidden());

            itemList[m_currentElement]->onSelect();
            break;

        case Qt::Key_Down:
            itemList[m_currentElement]->onDeselect();

            do
            {
                    ++m_currentElement %= itemList.size();
            }
            while (itemList[m_currentElement]->isHidden());

            itemList[m_currentElement]->onSelect();
            break;
    }}

void SubmenuItem::close()
{
    for (auto &&item : itemList)
    {
        item->setVisible(false);
        Menu::getInstance().layout()->removeWidget(item.get());
    }
}

bool SubmenuItem::isHidden()
{
    return itemList.size() == 0;
}
