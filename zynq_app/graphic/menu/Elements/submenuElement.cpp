#include "submenuElement.h"

SubmenuElement::SubmenuElement(QString text, ElementBase *parent) : ElementBase(text), parent(parent)
{
}

SubmenuElement::~SubmenuElement()
{

}

void SubmenuElement::execute()
{

}

// execute will set the current menu in display as this submenu
