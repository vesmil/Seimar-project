#ifndef VALUEITEM_H
#define VALUEITEM_H

#include <QLabel>

#include "library/controller/value.h"
#include "graphic/menu/items/itembase.h"

//! \brief Item which after confirmation will offer access to setting some value
class ValueItem : public ItemBase
{
public:
    ValueItem(const QString& text, IValue& value, SubmenuItem* parentMenu, QWidget* parentWidget = nullptr, bool live = false);

    void execute() override;
    void control(QKeyEvent* event) override;

    void refresh() override;
    bool isHidden() override;

private:
    void increase();
    void decrease();

    QLabel m_textLabel{};
    QLabel m_valueLabel{};

    IValue& m_value;

    bool m_liveView;
};

#endif // VALUEITEM_H
