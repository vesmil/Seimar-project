#include "menu.h"
#include "global/logCategories.h"

ElementBase *Menu::selectedElement = nullptr;
SubmenuElement *Menu::currentSubmenu = nullptr;
QVBoxLayout *Menu::layout = nullptr;

Menu::Menu(QWidget* parent) : QWidget(parent)
{
    root = std::make_unique<SubmenuElement>(QString{}, root.get(), this);
    root->setVisible(false);

    layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop);

    // TODO Where to build the menu? - this is just temp
    for (int i = 0; i < 5; i++)
    {
        root->elementList.emplace_back(std::make_unique<SubmenuElement>(QString::number(i), root.get(), this));
        layout->addWidget(root->elementList[i].get());
        root->elementList[i]->setVisible(false);

        for (int j = 0; j < 6; j++)
        {
            SubmenuElement* casted = static_cast<SubmenuElement*>((root->elementList[i]).get());
            casted->elementList.emplace_back(std::make_unique<SubmenuElement>(QString::number(i) + QString('a' + j), casted, this));
            casted->elementList[j]->setVisible(false);

            for (int k = 0; k < 10; k++)
            {
                SubmenuElement* casted2 = static_cast<SubmenuElement*>((casted->elementList[j]).get());
                casted2->elementList.emplace_back(std::make_unique<SubmenuElement>(QString::number(i) + QString('a' + j) + QString::number(k), casted, this));
                casted2->elementList[k]->setVisible(false);
            }
        }
    }
}

void Menu::keyPressEvent(QKeyEvent *event)
{
    if (!menuActive)
    {
        if (event->key() == Qt::Key_D)
            open();

        return;
    }

    switch (event->key())
    {
        case Qt::Key_A:
            if (currentSubmenu->parentMenu != nullptr)
                setSubmenu(currentSubmenu->parentMenu);
            else
                close();
            break;

        case Qt::Key_D:
            // selectedElement->execute();
            break;

        // TODO propagate on change to button
        case Qt::Key_Up:
            // ...
            // selectedElement->onChange();
            break;

        case Qt::Key_Down:
            // ...
            // selectedElement->onChange();
            break;
    }
}

void Menu::setSubmenu(SubmenuElement *submenu)
{
    for (auto &&item : currentSubmenu->elementList)
    {
        item->setVisible(false);
        layout->removeWidget(item.get());
    }

    currentSubmenu = submenu;

    for (auto &&item : currentSubmenu->elementList)
    {
        item->setVisible(true);
        layout->addWidget(item.get());
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

    // TODO Why segfault
    for (auto &&item : currentSubmenu->elementList)
    {
        item->setVisible(false);
    }
}
