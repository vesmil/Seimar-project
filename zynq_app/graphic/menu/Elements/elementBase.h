#ifndef ELEMENTBASE_H
#define ELEMENTBASE_H

#include <QString>
#include <QWidget>

/*!
 * \brief Base for items in menu
 */
class ElementBase : public QWidget
{
    Q_OBJECT

public:
    ElementBase(QString text) : text(text) {};

    // Cant be pure virtual because of ctor
    void execute() {};

    QString text{};
};

#endif // ELEMENTBASE_H
