#ifndef SUBMENUELEMENT_H
#define SUBMENUELEMENT_H

#include "elementBase.h"

#include <vector>
#include <memory>

struct SubmenuElement : public ElementBase
{
    SubmenuElement();

    std::vector<std::shared_ptr<ElementBase>> elementList;
};

#endif // SUBMENUELEMENT_H
