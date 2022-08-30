#include "submenuitem.h"

#include "graphic/menu/menu.h"
#include "global/logcategories.h"

SubmenuItem::SubmenuItem(QString text, SubmenuItem *parentMenu, QWidget *parent)
    : ItemBase(parent), parentMenu(parentMenu)
{
    ItemLayout* layout = new ItemLayout(this);

    m_text = new QLabel();
    m_text->setText(text);
    m_text->setVisible(true);

    layout->addWidget(m_text);
}

void SubmenuItem::execute()
{
    Menu::getInstance().setSubmenu(this);
}
