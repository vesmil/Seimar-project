#ifndef ITEMBASE_H
#define ITEMBASE_H

#include <QWidget>

//! \brief Base class for all items displayed in menu
class ItemBase : public QWidget
{
    Q_OBJECT
public:
    ItemBase(QWidget* parent);

    // should be pure virtual but I need ElemnetBase to have constructor...
    virtual void execute();

    virtual void select();
    virtual void deselect();

    virtual void control(QKeyEvent* event);

protected:
    using BaseClass = ItemBase;
};

#endif // ITEMBASE_H
