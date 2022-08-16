#ifndef VALUEELEMENT_H
#define VALUEELEMENT_H

#include "elementBase.h"

class ValueElement : public ElementBase
{
public:
    ValueElement(QWidget* parent);

private:
    // text part - button I guess
    // value part - text, arrows, slider, ... (will have custom class I guess)
};

#endif // VALUEELEMENT_H
