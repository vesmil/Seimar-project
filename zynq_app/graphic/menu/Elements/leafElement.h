#ifndef LEAFELEMENT_H
#define LEAFELEMENT_H

#include "elementBase.h"

// Should I nead leafElemnt from which ViscaElement, SetValueElement, GeneralElement will inherit

struct LeafElement : ElementBase
{
    LeafElement();

    void execute() override;
};

#endif // LEAFELEMENT_H
