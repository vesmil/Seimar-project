#include "menu.h"
#include "global/logCategories.h"

SubmenuItem *Menu::currentSubmenu = nullptr;
QVBoxLayout *Menu::layout = nullptr;
int Menu::currentElement = 0;

Menu::Menu(QWidget* parent) : QWidget(parent)
{
    root = std::make_unique<SubmenuItem>(QString{}, root.get(), this);
    root->setVisible(false);

    layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop);

    // TODO Where to build the menu? - also this is obvs just temp
    for (int i = 0; i < 5; i++)
    {
        root->elementList.emplace_back(std::make_unique<SubmenuItem>(QString::number(i), root.get(), this));
        layout->addWidget(root->elementList[i].get());
        root->elementList[i]->setVisible(false);

        for (int j = 0; j < 6; j++)
        {
            SubmenuItem* casted = static_cast<SubmenuItem*>((root->elementList[i]).get());
            casted->elementList.emplace_back(std::make_unique<SubmenuItem>(QString::number(i) + QString('a' + j), casted, this));
            casted->elementList[j]->setVisible(false);

            for (int k = 0; k < 10; k++)
            {
                SubmenuItem* casted2 = static_cast<SubmenuItem*>((casted->elementList[j]).get());
                casted2->elementList.emplace_back(std::make_unique<SubmenuItem>(QString::number(i) + QString('a' + j) + QString::number(k), casted, this));
                casted2->elementList[k]->setVisible(false);
            }
        }
    }
}

void Menu::keyPressEvent(QKeyEvent *event)
{
    if (!menuActive)
    {
        if (event->key() == Qt::Key_Right)
            open();

        return;
    }

    switch (event->key())
    {
        case Qt::Key_Left:
            if (currentSubmenu->parentMenu != nullptr)
                setSubmenu(currentSubmenu->parentMenu);
            else
                close();

            break;

        case Qt::Key_Right:
            currentSubmenu->elementList[currentElement]->execute();
            break;

        case Qt::Key_Up:
            currentElement -= 1;
            currentElement %= currentSubmenu->elementList.size();

            // selectedElement->onChange();
            break;

        case Qt::Key_Down:
            currentElement += 1;
            currentElement %= currentSubmenu->elementList.size();

            // selectedElement->onChange();
            break;
    }
}

void Menu::setSubmenu(SubmenuItem *submenu)
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
