#ifndef VALUE_H
#define VALUE_H

#include <QString>
#include "global/logcategories.h"

struct IValue
{
    virtual void set() = 0;
    virtual void setDefault() = 0;

    virtual void store() = 0;
    virtual void restorePrev() = 0;

    virtual QString getQString() = 0;

    virtual void operator++() = 0;
    virtual void operator--() = 0;
};

template<typename TVar, typename TContext>
struct Value : public IValue {
    Value(TVar defaultValue, TVar minValue, TVar maxValue, bool (TContext::*setFunc) (TVar), TContext* context, QString units = "")
        : m_value(defaultValue), m_units(units), m_default(m_value), m_min(minValue), m_max(maxValue), m_context(context), m_setFunc(setFunc)
    {
    }

    void set() override
    {
        bool result = (m_context->*m_setFunc)(m_value);
        if (!result)
        {
            m_value = m_prevValue;
        }
    }

    void setDefault() override
    {
        m_value = m_default;
        set();
    }

    void store() override
    {
        m_prevValue = TVar(m_value);
    }

    void restorePrev() override
    {
        m_value = m_prevValue;
    }

    QString getQString() override
    {
        return QString::number(m_value) + m_units;
    }

    void operator++() override
    {
        if(m_value < m_max)
        {
            m_value = (TVar) (m_value + 1);
        }
    }

    void operator--() override
    {
        if(m_value > m_min)
        {
            m_value = (TVar) (m_value - 1);
        }
    }

private:
    TVar m_value;
    QString m_units;

    TVar m_default;
    TVar m_min;
    TVar m_max;

    TVar m_prevValue;

    TContext* m_context;
    bool (TContext::*m_setFunc) (TVar);
};

#endif // VALUE_H
