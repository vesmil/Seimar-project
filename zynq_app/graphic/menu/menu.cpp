#include "menu.h"
#include "global/logCategories.h"
#include "items/valueItem.h"

SubmenuItem *Menu::m_currentSubmenu = nullptr;
QVBoxLayout *Menu::m_layout = nullptr;
std::unique_ptr<SubmenuItem> Menu::m_root = nullptr;

Menu::Mode Menu::m_currentMode = INACTIVE;

std::size_t Menu::m_currentElement = 0;
std::stack<std::size_t> Menu::m_indexstack{};


Menu::Menu(QWidget* parent) : QWidget(parent)
{
    m_root = std::make_unique<SubmenuItem>(QString{}, m_root.get(), this);
    m_root->setVisible(false);

    m_layout = new QVBoxLayout(this);
    m_layout->setAlignment(Qt::AlignTop);

    // TODO Where to build the menu? - also this is obvs just temp

    for (int i = 0; i < 5; i++)
    {
        m_root->elementList.emplace_back(std::make_unique<SubmenuItem>(QString::number(i), m_root.get(), this));
        m_layout->addWidget(m_root->elementList[i].get());
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
        {
            open();
        }
        break;

    case ACTIVE:
        menuNav(event);
        break;

    case EXEC:
        // m_currentSubmenu->elementList[m_currentElement]->keyPressEvent(event);
        break;
    }
}

void Menu::menuNav(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Left:
        m_currentSubmenu->elementList[m_currentElement]->setStyleSheet("background-color:transparent;");

        if (m_currentSubmenu->parentMenu != nullptr)
        {
            std::size_t index = m_indexstack.top();
            m_indexstack.pop();

            setSubmenu(m_currentSubmenu->parentMenu, index);
        }
        else
        {
            close();
        }

        break;

    case Qt::Key_Right:
        // TODO find somewhere and better way to change color on hover
        m_indexstack.push(m_currentElement);

        m_currentSubmenu->elementList[m_currentElement]->setStyleSheet("background-color:transparent;");

        m_currentSubmenu->elementList[m_currentElement]->execute();

        // TODO Well what happens on valueItem? - Settings moved to item bool

        break;

    case Qt::Key_Up:
        m_currentSubmenu->elementList[m_currentElement]->setStyleSheet("background-color:transparent;");

        m_currentElement = m_currentElement == 0? m_currentSubmenu->elementList.size() : m_currentElement;
        --m_currentElement;

        m_currentSubmenu->elementList[m_currentElement]->setStyleSheet("background-color:lightgrey;");

        break;

    case Qt::Key_Down:
        m_currentSubmenu->elementList[m_currentElement]->setStyleSheet("background-color:transparent;");

        ++m_currentElement %= m_currentSubmenu->elementList.size();

        m_currentSubmenu->elementList[m_currentElement]->setStyleSheet("background-color:lightgrey;");

        break;
    }
}

void Menu::setSubmenu(SubmenuItem *submenu, std::size_t index)
{
    if (m_currentSubmenu != nullptr)
    {
        for (auto &&item : m_currentSubmenu->elementList)
        {
            item->setVisible(false);
            m_layout->removeWidget(item.get());
        }
    }

    m_currentSubmenu = submenu;

    for (auto &&item : m_currentSubmenu->elementList)
    {
        item->setVisible(true);
        m_layout->addWidget(item.get());
    }

    m_currentElement = index;
    m_currentSubmenu->elementList[m_currentElement]->setStyleSheet("background-color:lightgrey;");
}

void Menu::open()
{
    m_currentMode = ACTIVE;
    setSubmenu(m_root.get());
}

void Menu::close()
{
    m_currentMode = INACTIVE;

    for (auto &&item : m_currentSubmenu->elementList)
    {
        item->setVisible(false);
    }
}
