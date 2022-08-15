#ifndef ELEMENTBASE_H
#define ELEMENTBASE_H

#include <QString>

/*!
 * \brief Base for items in menu
 */
struct ElementBase
{
    ElementBase(QString text);

    // Cant be pure virtual because of ctor
    void execute() {};

    QString text{};
};

#endif // ELEMENTBASE_H
