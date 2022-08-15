#include "menuDisplay.h"

#include <QVBoxLayout>

MenuDisplay::MenuDisplay(QWidget* parent) : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    layout->setAlignment(Qt::AlignTop);

    // Create and hide empty buttons
    for (int i = 0; i < 10; i++)
    {
        /* buttons.emplace_back(std::make_unique<QPushButton>(this));
        buttons[i]->setText("AAA");
        buttons[i]->setVisible(true);
        layout->addWidget(buttons[i].get()); */

        QPushButton* button = new QPushButton;
        button->setText("AAA");
        button->setVisible(true);
        layout->addWidget(button);
    }

    setLayout(layout);
}

void MenuDisplay::show()
{
    /*
    for (std::size_t i = 0; i < currentSubmenu->elementList.size(); i++)
    {
        buttons[i]->setVisible(true);
        buttons[i]->setText(currentSubmenu->elementList[i]->text);
    }
    */
}

void MenuDisplay::hide()
{
    for (std::size_t i = 0; i < currentSubmenu->elementList.size(); i++)
    {
        buttons[i]->setVisible(false);
    }
}
