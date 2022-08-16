#ifndef ITEMBASE_H
#define ITEMBASE_H

#include <QWidget>

class ItemBase : public QWidget
{
    Q_OBJECT
public:
    ItemBase(QWidget* parent) : QWidget(parent) {};

    // should be pure virtual but I need ElemnetBase to have constructor... mby
    virtual void execute() {}
    virtual void onChange() {}
};

#endif // ITEMBASE_H
