#ifndef ELEMENTBASE_H
#define ELEMENTBASE_H

#include <QString>

struct ElementBase
{
    ElementBase(QString text /* ... */ );

    virtual void execute() = 0;

    QString text; // TODO add getter setter
    bool hidden; // as not allowed and displayed with grey font
    ElementBase *parent;
};

#endif // ELEMENTBASE_H
