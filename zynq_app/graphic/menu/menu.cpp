#include "menu.h"
#include "global/logCategories.h"
#include "items/valueItem.h"

SubmenuItem *Menu::currentSubmenu = nullptr;
QVBoxLayout *Menu::layout = nullptr;
std::size_t Menu::currentElement = 0;

Menu::Menu(QWidget* parent) : QWidget(parent)
{
    m_root = std::make_unique<SubmenuItem>(QString{}, m_root.get(), this);
    m_root->setVisible(false);

    layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop);

    // TODO Where to build the menu? - also this is obvs just temp
    // new class or just a method?

    for (int i = 0; i < 5; i++)
    {
        m_root->elementList.emplace_back(std::make_unique<SubmenuItem>(QString::number(i), m_root.get(), this));
        layout->addWidget(m_root->elementList[i].get());
        m_root->elementList[i]->setVisible(false);

        for (int j = 0; j < 6; j++)
        {
            SubmenuItem* casted = static_cast<SubmenuItem*>((m_root->elementList[i]).get());
            casted->elementList.emplace_back(std::make_unique<SubmenuItem>(QString::number(i) + QString('a' + j), casted, this));
            casted->elementList[j]->setVisible(false);

            for (int k = 0; k < 10; k++)
            {
                SubmenuItem* casted2 = static_cast<SubmenuItem*>((casted->elementList[j]).get());
                casted2->elementList.emplace_back(std::make_unique<ValueItem>(this /*QString::number(i) + QString('a' + j) + QString::number(k), casted, this*/));
                casted2->elementList[k]->setVisible(false);
            }
        }
    }
}

void Menu::keyPressEvent(QKeyEvent *event)
{
    switch (m_currentMode)
    {
    case INACTIVE:
        if (event->key() == Qt::Key_Right)
            open();

        break;

    case ACTIVE:
        menuNav(event);
        break;

    case EXEC:
        // TODO forward the controls
        break;
    }
}

void Menu::menuNav(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Left:
        if (currentSubmenu->parentMenu != nullptr)
        {
            // TODO remember index
            setSubmenu(currentSubmenu->parentMenu, 0);

        }
        else
            close();

        break;

    case Qt::Key_Right:
        // TODO find somewhere and better way to change color on hover
        currentSubmenu->elementList[currentElement]->setStyleSheet("background-color:transparent;");
        currentSubmenu->elementList[currentElement]->execute();

        // TODO Well what happens on valueItem? - Settings moved to item bool

        break;

    case Qt::Key_Up:
        currentSubmenu->elementList[currentElement]->setStyleSheet("background-color:transparent;");
        currentElement = currentElement == 0? currentSubmenu->elementList.size() : currentElement;
        --currentElement;
        currentSubmenu->elementList[currentElement]->setStyleSheet("background-color:grey;");

        break;

    case Qt::Key_Down:
        currentSubmenu->elementList[currentElement]->setStyleSheet("background-color:transparent;");
        ++currentElement %= currentSubmenu->elementList.size();
        currentSubmenu->elementList[currentElement]->setStyleSheet("background-color:grey;");

        break;
    }
}

void Menu::setSubmenu(SubmenuItem *submenu, std::size_t index)
{
    if (currentSubmenu != nullptr)
    {
        for (auto &&item : currentSubmenu->elementList)
        {
            item->setVisible(false);
            layout->removeWidget(item.get());
        }
    }

    currentSubmenu = submenu;

    for (auto &&item : currentSubmenu->elementList)
    {
        item->setVisible(true);
        layout->addWidget(item.get());
    }

    currentElement = index;
    currentSubmenu->elementList[currentElement]->setStyleSheet("background-color:grey;");
}

void Menu::open()
{
    m_currentMode = ACTIVE;
    setSubmenu(m_root.get());
}

void Menu::close()
{
    m_currentMode = INACTIVE;

    for (auto &&item : currentSubmenu->elementList)
    {
        item->setVisible(false);
    }
}
