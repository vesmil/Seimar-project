#ifndef ELEMENTBASE_H
#define ELEMENTBASE_H

#include <QString>

struct ElementBase
{
    ElementBase(QString text);
    virtual void execute() = 0;

    QString text;
};

#endif // ELEMENTBASE_H
