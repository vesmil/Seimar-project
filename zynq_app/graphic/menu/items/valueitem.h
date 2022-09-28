#ifndef VALUEITEM_H
#define VALUEITEM_H

#include <QLabel>

#include "library/controller/elements/setter.h"
#include "graphic/menu/items/itembase.h"

//! \brief Item which after confirmation will set some value using passed function
class ValueItem : public ItemBase
{
public:
    /*!
     * \param text Text displayed in menu
     * \param value Complex Value object which will be used to set value
     * \param parentMenu Parent menu to go to after confirmation
     * @param parentWidget Parent widget as for all Qt widgets
     * @param live Determines if value should be updated after every change
     */
    ValueItem(const QString& text, ISetter* value, SubmenuItem* parentMenu, QWidget* parentWidget = nullptr, bool live = false);

    void execute() override;
    void control(QKeyEvent* event) override;

    void refresh() override;
    bool isHidden() override;

private:
    void increase();
    void decrease();

    QLabel m_textLabel{};
    QLabel m_valueLabel{};

    ISetter* m_value;

    bool m_liveView;
};

#endif // VALUEITEM_H
