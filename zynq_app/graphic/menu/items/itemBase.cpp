#include "itemBase.h"


ItemBase::ItemBase(QWidget* parent) : QWidget(parent)
{

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
