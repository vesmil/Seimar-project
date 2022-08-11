#include "menu.h"

Menu::Menu()
{
}

void Menu::display()
{
    // iterate all elements in list and create button for them
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
    currentSubmenu = root;
    display();
}

void Menu::close()
{
    //
}
