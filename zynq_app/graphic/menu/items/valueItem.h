#ifndef VALUEITEM_H
#define VALUEITEM_H

#include <QLabel>

#include "graphic/menu/items/itembase.h"
#include "graphic/menu/menu.h"

// TODO version with getter and setter method passed by param

//! \brief Item which after confirmation will offer access to setting some value
template<typename T>
class ValueItem : public ItemBase
{
public:
    ValueItem(const QString& text, T& variable, QWidget* parent) : ItemBase(parent), valueRef(variable)
    {
        ItemLayout* layout = new ItemLayout(this);

        textLabel.setText(text);
        layout->addWidget(&textLabel);

        valueLabel.setText(QString::number(variable));
        layout->addWidget(&valueLabel);
    }

    void execute() override
    {
        ItemBase::execute();
        Menu::getInstance().startExec();
        tempSave = valueRef;
    }

    void control(QKeyEvent* event) override
    {
        switch (event->key())
        {
        case Qt::Key_Left:
            valueRef = tempSave;
            valueLabel.setText(QString::number(valueRef));
            Menu::getInstance().completeExec();
            break;

        case Qt::Key_Right:
            Menu::getInstance().completeExec();
            break;

        case Qt::Key_Up:
            valueRef++;
            valueLabel.setText(QString::number(valueRef));
            break;

        case Qt::Key_Down:
            valueRef--;
            valueLabel.setText(QString::number(valueRef));
            break;
        }
    }

private:
    QLabel textLabel{};
    QLabel valueLabel{};

    T& valueRef;
    T tempSave;
};

#endif // VALUEITEM_H
