#ifndef ITEMBASE_H
#define ITEMBASE_H

#include <QWidget>

class ItemBase : public QWidget
{
    Q_OBJECT
public:
    ItemBase(QWidget* parent) : QWidget(parent) {};

    // should be pure virtual but I need ElemnetBase to have constructor
    virtual void execute() {}
    virtual void onChange() {}

    // void keyPress(QKeyEvent*) {}
    // TODO I probably need smth on leave and keyPress
};

#endif // ITEMBASE_H
