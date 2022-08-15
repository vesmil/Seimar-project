#ifndef SUBMENUELEMENT_H
#define SUBMENUELEMENT_H

#include "elementBase.h"

#include <vector>
#include <memory>

/*!
 * \brief Menu element from which next menu will be opened
 */
struct SubmenuElement : public ElementBase
{
    SubmenuElement(QString text, ElementBase *parent);
    ~SubmenuElement();

    void execute();

    ElementBase* parent;
    std::vector<std::unique_ptr<ElementBase>> elementList;
};

#endif // SUBMENUELEMENT_H
