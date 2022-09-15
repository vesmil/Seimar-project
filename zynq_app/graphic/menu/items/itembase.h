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

    virtual void executeSelected();
    virtual void onSelect();
    virtual void onDeselect();
    virtual void control(QKeyEvent* event);

    virtual void refresh();
    virtual bool isHidden();

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
