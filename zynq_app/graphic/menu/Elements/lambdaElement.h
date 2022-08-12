#ifndef LAMBDAELEMENT_H
#define LAMBDAELEMENT_H

#include "elementBase.h"

// TODO redo

template<typename TFunc>
struct LambdaElement : ElementBase
{
    /*!
     * \warning creating new child of elementBase is prefered over lambda element
     */
    LambdaElement(QString text, TFunc func) : ElementBase(text), execFunction(func) {}

    void execute() override
    {
        execFunction();
    }

private:
    TFunc execFunction;
};

#endif // LAMBDAELEMENT_H
