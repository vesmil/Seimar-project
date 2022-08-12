#include "menuDisplay.h"

#include <QVBoxLayout>

MenuDisplay::MenuDisplay(QWidget* parent) : QWidget(parent)
{

    // Create and hide layout with background color
    QVBoxLayout* layout = new QVBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->setAlignment(Qt::AlignTop);
    // layout->setSizeConstraint(QLayout::SetFixedSize);

/*
    // Create and hide empty buttons
    for (int i = 0; i < 10; i++)
    {
        // buttons.emplace_back(std::make_unique<QPushButton>());
        buttons.emplace_back();
        buttons[i]->setVisible(false);
        layout->addWidget(buttons[i].get());
    }
*/

    // setLayout(layout);
}

void MenuDisplay::show()
{
    for (std::size_t i = 0; i < currentSubmenu->elementList.size(); i++)
    {
        buttons[i]->setVisible(true);
        buttons[i]->setText(currentSubmenu->elementList[i]->text);
    }
}

void MenuDisplay::hide()
{
    for (std::size_t i = 0; i < currentSubmenu->elementList.size(); i++)
    {
        buttons[i]->setVisible(false);
    }
}
