#ifndef ELEMENTBASE_H
#define ELEMENTBASE_H

#include <QWidget>

class ElementBase : public QWidget
{
    Q_OBJECT

public:
    ElementBase(QWidget* parent) : QWidget(parent) {};

    // should be pure virtual but I need ElemnetBase to have constructor... mby
    void execute();
    void onChange();
};

#endif // ELEMENTBASE_H
