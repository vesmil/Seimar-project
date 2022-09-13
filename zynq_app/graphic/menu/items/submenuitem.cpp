#include "submenuitem.h"

#include "graphic/menu/menu.h"
#include "global/logcategories.h"

#include <graphic/style.h>

SubmenuItem::SubmenuItem(QString text, SubmenuItem *parentMenu, QWidget *parent)
    : ItemBase(parent),
      parentMenu(parentMenu)
{
    ItemLayout* layout = new ItemLayout(this);

    m_text = new QLabel(this);
    m_text->setText(text);
    m_text->setVisible(true);

    layout->addWidget(m_text);
}

void SubmenuItem::open()
{
    Menu::getInstance().setSubmenu(this);

    if (itemList.size() == 0)
    {
        parentMenu->open();  // TODO show some pop-up
        qCWarning(uiLog()) << "Empty submenu";
        return;
    }

    for (auto &&item : itemList)
    {
        if (!item->isHidden())
        {
            item->setVisible(true);
            Menu::getInstance().layout()->addWidget(item.get());
        }
    }

    itemList[m_currentElement]->select();
}

void SubmenuItem::exit()
{
    for (auto &&item : itemList)
    {
        item->setVisible(false);
        Menu::getInstance().layout()->removeWidget(item.get());
    }
}


void SubmenuItem::control(QKeyEvent* event)
{
    switch (event->key())
    {
    case Qt::Key_Left:
        itemList[m_currentElement]->setStyleSheet(Style::getInstance().menu.item);

        if (parentMenu)
        {
            exit();
            parentMenu->open();
        }
        else
        {
            Menu::getInstance().exit();
        }

        break;

    case Qt::Key_Right:
        exit();
        itemList[m_currentElement]->deselect();
        itemList[m_currentElement]->open();
        break;

    case Qt::Key_Up:
        itemList[m_currentElement]->deselect();

        do
        {
            m_currentElement = m_currentElement == 0? itemList.size() : m_currentElement;
            --m_currentElement;
        } while (itemList[m_currentElement]->isHidden());

        itemList[m_currentElement]->select();
        break;

    case Qt::Key_Down:
        itemList[m_currentElement]->deselect();

        do
        {
                ++m_currentElement %= itemList.size();
        } while (itemList[m_currentElement]->isHidden());

        itemList[m_currentElement]->select();
        break;
    }
}
