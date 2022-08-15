#include "submenuElement.h"

SubmenuElement::SubmenuElement(QString text, ElementBase *parent) : ElementBase(text), parent(parent)
{
    // TODO solve the vtable problem...
}

SubmenuElement::~SubmenuElement()
{

}

// execute will set the current menu in display as this submenu
