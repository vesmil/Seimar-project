#ifndef POPUPELEMENT_H
#define POPUPELEMENT_H

#include "elementBase.h"

class PopupElement : public ElementBase
{
public:
    PopupElement(QWidget* parent);

    void execute();
};

#endif // POPUPELEMENT_H
