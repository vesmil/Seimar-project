#include "itembase.h"

#include <graphic/style.h>
#include <QPalette>

ItemBase::ItemBase(QWidget* parent) : QWidget(parent)
{
    setVisible(false);
    setAutoFillBackground(true);
}

void ItemBase::execute()
{    
    setPalette(Style::getInstance().menu.executedItem);
}

void ItemBase::select()
{
    setPalette(Style::getInstance().menu.selectedItem);
}

void ItemBase::deselect()
{
    setPalette(Style::getInstance().menu.item);
}

void ItemBase::control(QKeyEvent*)
{

}
