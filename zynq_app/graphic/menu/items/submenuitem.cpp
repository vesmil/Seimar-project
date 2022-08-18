#include "submenuitem.h"

#include <QHBoxLayout>
#include "../menu.h"

#include "global/logCategories.h"

SubmenuItem::SubmenuItem(QString text, SubmenuItem *parentMenu, QWidget *parent)
    : ItemBase(parent), parentMenu(parentMenu)
{
    QHBoxLayout* layout = new QHBoxLayout(this);

    layout->setMargin(0);
    layout->setSpacing(0);

    m_text = new QLabel();
    m_text->setText(text);
    m_text->setVisible(true);

    layout->addWidget(m_text);
}

void SubmenuItem::execute()
{
    qCInfo(uiLog()) << "execute";
    Menu::getInstance().setSubmenu(this);
}

// execute will set the current menu in display as this submenu
