#include "menu.h"
#include "global/logCategories.h"

Menu::Menu(QWidget* parent) : display(parent)
{
    // Generate all menu levels?
}


void Menu::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_Left:
            qCInfo(uiLog()) << "left";

            // close();
            break;
        case Qt::Key_E:
            open();
            qCInfo(uiLog()) << "r";

            break;
        case Qt::Key_Up:
            // (ʌ,v) change selectedElement
            break;
        case Qt::Key_Down:
            break;
    }
}

void Menu::open()
{
    menuActive = true;
    display.currentSubmenu = root.get();
    display.show();
}

void Menu::close()
{
    menuActive = false;
    display.hide();
}

