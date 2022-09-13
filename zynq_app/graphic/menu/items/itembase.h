#ifndef ITEMBASE_H
#define ITEMBASE_H

#include <QHBoxLayout>
#include <QWidget>

//! \brief Base class for all items displayed in menu
class ItemBase : public QWidget
{
    Q_OBJECT
public:
    ItemBase(QWidget* parent);

    virtual bool isHidden();

    virtual void execute();
    virtual void select();
    virtual void deselect();

    virtual void control(QKeyEvent* event);

protected:
    using BaseClass = ItemBase;
};


class ItemLayout : public QHBoxLayout
{
    Q_OBJECT

public:

    ItemLayout(QWidget *parent) : QHBoxLayout(parent)
    {
        setMargin(0);
        setSpacing(0);
    }
};

#endif // ITEMBASE_H
