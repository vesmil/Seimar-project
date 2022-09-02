#include "itembase.h"

#include <graphic/style.h>
#include <QPalette>

ItemBase::ItemBase(QWidget* parent) : QWidget(parent)
{
    setVisible(false);
    setStyleSheet(Style::getInstance().menu.item);
}

void ItemBase::execute()
{    
    setStyleSheet(Style::getInstance().menu.executedItem);
}

void ItemBase::select()
{
    setStyleSheet(Style::getInstance().menu.selectedItem);
}

void ItemBase::deselect()
{
    setStyleSheet(Style::getInstance().menu.item);
}

void ItemBase::control(QKeyEvent*)
{

}

bool ItemBase::isHidden()
{
    return false;
}
