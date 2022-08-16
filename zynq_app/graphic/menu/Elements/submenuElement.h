#ifndef SUBMENUELEMENT_H
#define SUBMENUELEMENT_H

#include <vector>
#include <memory>
#include <qpushbutton.h>

#include "elementBase.h"

/*!
 * \brief Menu element from which next menu will be opened
 */
class SubmenuElement : public ElementBase
{
public:
    SubmenuElement(QString text, SubmenuElement *parentMenu, QWidget *parent = nullptr);
    ~SubmenuElement();

    void execute();

    QPushButton* button;

    SubmenuElement* parentMenu;
    std::vector<std::unique_ptr<ElementBase>> elementList{};
};

#endif // SUBMENUELEMENT_H
