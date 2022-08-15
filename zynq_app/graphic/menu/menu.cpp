#include "menu.h"
#include "global/logCategories.h"

#include <QVBoxLayout>

Menu::Menu(QWidget* parent) : QWidget(parent), root(std::make_unique<SubmenuElement>(QString{}))
{
    QVBoxLayout* layout = new QVBoxLayout();

    layout->setAlignment(Qt::AlignTop);

    // Create and hide empty buttons
    for (int i = 0; i < 10; i++)
    {
        root->elementList.emplace_back<>();
    }

    open();
}


void Menu::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_A:
            qCInfo(uiLog()) << "left";
            close();
            break;

        case Qt::Key_D:
            show();
            qCInfo(uiLog()) << "r";
            break;

        case Qt::Key_Up:
            break;

        case Qt::Key_Down:
            break;
    }
}

void Menu::open()
{
    menuActive = true;
    currentSubmenu = root.get();

    // Draw all widgets in current submenu
}

void Menu::close()
{
    menuActive = false;
}
