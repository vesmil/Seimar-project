#ifndef ELEMENTBASE_H
#define ELEMENTBASE_H

#include <QWidget>

class ElementBase : public QWidget
{
    Q_OBJECT

public:
    ElementBase(QWidget* parent) : QWidget(parent) {};

    void execute() {};
};

#endif // ELEMENTBASE_H
