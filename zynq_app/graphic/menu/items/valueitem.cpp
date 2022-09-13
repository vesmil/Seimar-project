#include "valueitem.h"

ValueItem::ValueItem(const QString& text, IValue& value, QWidget* parent, bool live)
    : ItemBase(parent), m_value(value), m_liveView(live)
{
    ItemLayout* layout = new ItemLayout(this);

    m_textLabel.setText(text);
    layout->addWidget(&m_textLabel);

    m_valueLabel.setText(m_value.getQString());
    m_valueLabel.setAlignment(Qt::AlignRight);

    layout->addWidget(&m_valueLabel);
}

void ValueItem::open()
{
    ItemBase::open();
    // Menu::getInstance().startExec();
    m_value.store();
}

void ValueItem::exit()
{

}



void ValueItem::control(QKeyEvent* event)
{
    switch (event->key())
    {
        case Qt::Key_Left:
            m_value.restorePrev();
            // Menu::getInstance().completeExec();
            break;

        case Qt::Key_Right:
            m_value.set();
            // Menu::getInstance().completeExec();
            break;

        case Qt::Key_Up:
            ++m_value;
            if (m_liveView)
            {
                m_value.set();
            }
            break;

        case Qt::Key_Down:
            --m_value;
            if (m_liveView)
            {
                m_value.set();
            }
            break;

        default:
            return;
    }

    // It's better to set the text in all cases
    m_valueLabel.setText(m_value.getQString());
}

bool ValueItem::isHidden()
{
    return m_value.isHidden();
}
