#include "menu.h"

Menu::Menu()
{
    // Generate all menu levels?
}


void Menu::keyPressEvent(QKeyEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        switch (event->key())
        {
            // (>) call action on selectedElement
            // (ʌ,v) change selectedElement
            // (<) goBack or exit
        }
    }
}

void Menu::open()
{
    // will put root to current submenu in display...
    // will switch on the key press handler
    // will call show on menu display
}

