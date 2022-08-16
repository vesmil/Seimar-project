#include "menu.h"
#include "global/logCategories.h"

#include <QVBoxLayout>

Menu::Menu(QWidget* parent) : QWidget(parent)
{
    root = std::make_unique<SubmenuElement>(QString{}, root.get(), this);
    root->setVisible(false);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop);

    for (int i = 0; i < 10; i++)
    {
        root->elementList.emplace_back(std::make_unique<SubmenuElement>("...", root.get(), this));
        layout->addWidget(root->elementList[i].get());
        root->elementList[i]->setVisible(true);
    }
}


void Menu::keyPressEvent(QKeyEvent *event)
{
    // if menuOpen vs notOpen

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
            // ...
            break;

        case Qt::Key_Down:
            // ...
            break;
    }
}

void Menu::open()
{
    menuActive = true;
    currentSubmenu = root.get();

    for (auto &&item : currentSubmenu->elementList)
    {
        item->setVisible(true);
    }
}

void Menu::close()
{
    menuActive = false;

    for (auto &&item : currentSubmenu->elementList)
    {
        // item->setVisible(false);
    }
}
