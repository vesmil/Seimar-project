#include "itembase.h"

#include <graphic/qtpalettes.h>
#include <QPalette>

ItemBase::ItemBase(QWidget* parent) : QWidget(parent)
{
    setVisible(false);
    setAutoFillBackground(true);
}

void ItemBase::execute()
{    
    setPalette(QtPalettes::getInstance().menu.executedItem);
}

void ItemBase::select()
{
    setPalette(QtPalettes::getInstance().menu.selectedItem);
}

void ItemBase::deselect()
{
    setPalette(QtPalettes::getInstance().menu.item);
}

void ItemBase::control(QKeyEvent*)
{

}
