#ifndef VALUEITEM_H
#define VALUEITEM_H

#include <QLabel>

#include "library/controller/controller.h"
#include "graphic/menu/items/itembase.h"
#include "graphic/menu/menu.h"
#include "graphic/menu/items/value.h"

//! \brief Item which after confirmation will offer access to setting some value
class ValueItem : public ItemBase
{
public:
    // TODO How to solve missing context?

    ValueItem(const QString& text, IValue& value, QWidget* parent = nullptr, bool live = false);

    void execute() override;
    void control(QKeyEvent* event) override;

private:
    QLabel m_textLabel{};
    QLabel m_valueLabel{};

    IValue& m_value;

    bool m_liveView;
};

#endif // VALUEITEM_H
