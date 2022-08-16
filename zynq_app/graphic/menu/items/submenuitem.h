#ifndef SUBMENUITEM_H
#define SUBMENUITEM_H

#include <vector>
#include <memory>
#include <qpushbutton.h>

#include "itemBase.h"
#include "displayElements/button.h"

/*!
 * \brief Menu element from which next menu will be opened
 */
class SubmenuItem : public ItemBase
{
public:
    SubmenuItem(QString text, SubmenuItem *parentMenu, QWidget *parent = nullptr);

    void execute();

    // TODO it wont be a button but an UI element
    Button* button;

    SubmenuItem* parentMenu;
    std::vector<std::unique_ptr<ItemBase>> elementList{};
};

#endif // SUBMENUITEM_H
