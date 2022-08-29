#include "itembase.h"

ItemBase::ItemBase(QWidget* parent) : QWidget(parent)
{
    setVisible(false);
}

void ItemBase::execute()
{
    setStyleSheet("background-color: cyan");
}

void ItemBase::select()
{
    setStyleSheet("background-color: lightGray");
}

void ItemBase::deselect()
{
    setStyleSheet("background-color: transparent");
}

void ItemBase::control(QKeyEvent*)
{

}
