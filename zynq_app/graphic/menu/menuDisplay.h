#ifndef MENUDISPLAY_H
#define MENUDISPLAY_H

#include <qpushbutton.h>
#include <vector>

#include "Elements/submenuElement.h"

// Holds all the buttons, sets text, shows/hides
class menuDisplay
{
public:
    menuDisplay();

    void show();
    void hide();

private:
    std::vector<QPushButton> buttons;

    SubmenuElement* currentSubmenu;
    ElementBase* selectedElement;  // mby just index
};

#endif // MENUDISPLAY_H
