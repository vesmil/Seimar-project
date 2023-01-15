#ifndef TEXTSETTER_H
#define TEXTSETTER_H

#include <QString>
#include "library/controller/elements/setter.h"

template<typename TContext>
class TextSetter : public ValueSetter<QString, TContext>
{
public:
    TextSetter(QString& text, bool (TContext::*setFunc) (QString), TContext* context) : ValueSetter<QString, TContext>(NULL, setFunc, context), m_text(text) {}

    bool isControlable() override
    {
        return true;
    }

    void control(QKeyEvent* event) override
    {
        if (event->key() == Qt::Key_1)
        {
            m_text = "1";
            this->set();
        }
    }

    QString getValue() override
    {
        return m_text;
    }

    // Increase and decrease are pointless
    void increase() override {}
    void decrease() override {}

private:
    QString& m_text;
};

//! \brief Creates unique pointer to text value - used to elimainate need for template args.
template<typename TContext>
static auto makeTextval(/* ... */)
{
    return std::make_unique<TextSetter<TContext>>(/* ... */);
}


#endif // TEXTSETTER_H
