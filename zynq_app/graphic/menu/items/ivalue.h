#ifndef IVALUE_H
#define IVALUE_H

#include <qstring.h>

class IValueSetter
{
public:
    virtual void setAsync() = 0;
    virtual void set() = 0;

    virtual void store() = 0;
    virtual void restorePrev() = 0;
    virtual void setDefault() = 0;

    virtual bool hasChanged() = 0;

    virtual QString getQString() = 0;

    virtual void operator++() = 0;
    virtual void operator--() = 0;

    virtual bool isHidden() = 0;
};

#endif // IVALUE_H
