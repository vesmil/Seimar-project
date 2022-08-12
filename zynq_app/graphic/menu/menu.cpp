#include "menu.h"

Menu::Menu(QWidget* parent) : display(parent)
{
    // Generate all menu levels?
}


void Menu::keyPressEvent(QKeyEvent *event)
{
    if (menuActive && event->type() == QEvent::KeyPress)
    {
        switch (event->key())
        {
            case Qt::Key_Left:
                // (>) call action on selectedElement
                break;
            case Qt::Key_Right:
                // (<) goBack or exit
                break;
            case Qt::Key_Up:
                // (ʌ,v) change selectedElement
                break;
            case Qt::Key_Down:
                break;
        }
    }
}

void Menu::open()
{
    menuActive = true;
    // display.currentSubmenu = root.get();
    // display.show();
}

