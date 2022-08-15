#ifndef MENUDISPLAY_H
#define MENUDISPLAY_H

#include <qpushbutton.h>
#include <vector>

#include "Elements/submenuElement.h"

/*!
 * \brief Stores the menu QButtons - showing/hiding, seting texts
 */
class MenuDisplay : public QWidget
{
    Q_OBJECT

public:
    MenuDisplay(QWidget* parent = nullptr);
    ~MenuDisplay() = default;

    void show();
    void hide();

    SubmenuElement *currentSubmenu; // TODO ...

private:
    std::vector<std::unique_ptr<QPushButton>> buttons;

    ElementBase *selectedElement;
};

#endif // MENUDISPLAY_H
