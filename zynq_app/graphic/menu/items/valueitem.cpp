#include "valueitem.h"

#include <QKeyEvent>
#include "graphic/menu/menu.h"

ValueItem::ValueItem(const QString& text, IValueSetter& value, SubmenuItem* parentMenu, QWidget* parentWidget, bool live)
    : ItemBase(parentWidget, parentMenu),
      m_value(value),
      m_liveView(live)
{
    ItemLayout* layout = new ItemLayout(this);

    m_textLabel.setText(text);
    layout->addWidget(&m_textLabel);

    m_valueLabel.setText(m_value.getQString());
    m_valueLabel.setAlignment(Qt::AlignRight);

    layout->addWidget(&m_valueLabel);
}

void ValueItem::execute()
{
    ItemBase::execute();
    m_value.store();
}

void ValueItem::control(QKeyEvent* event)
{
    switch (event->key())
    {
        case Qt::Key_Left:
            if (m_value.hasChanged())
            {
                m_value.restorePrev();
                if (m_liveView)
                {
                    m_value.setAsync();
                }
            }
            Menu::getInstance().setOnSubmenu(m_parentMenu);
            break;

        case Qt::Key_Right:
            if (!m_liveView && m_value.hasChanged())
            {
                m_value.setAsync();
            }
            Menu::getInstance().setOnSubmenu(m_parentMenu);
            break;

        case Qt::Key_Up:
            increase();
            break;

        case Qt::Key_Down:
            decrease();
            break;

        default:
            return;
    }

    m_valueLabel.setText(m_value.getQString());
}

void ValueItem::refresh()
{
    m_valueLabel.setText(m_value.getQString());
}

bool ValueItem::isHidden()
{
    return m_value.isHidden();
}

void ValueItem::increase()
{
    ++m_value;
    if (m_liveView)
    {
        m_value.setAsync();
    }
}

void ValueItem::decrease()
{
    --m_value;
    if (m_liveView)
    {
        m_value.setAsync();
    }
}
