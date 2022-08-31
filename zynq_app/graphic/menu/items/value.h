#ifndef VALUE_H
#define VALUE_H

#include <QString>

struct IValue
{
    virtual void set() = 0;
    virtual void store() = 0;
    virtual void restore() = 0;

    virtual QString getQString() = 0;

    virtual IValue& operator++() = 0;
    virtual IValue& operator--() = 0;
};

template<typename TVar, typename TContext>
struct Value : public IValue {
    Value(TVar& value, bool (TContext::*setFunc) (TVar), TContext* context) : m_value(value), m_setFunc(setFunc), m_context(context) {}

    void set() override
    {
        (m_context->*m_setFunc)(m_value);
    }

    void store() override
    {
        m_prevValue = TVar(m_value);
    }

    void restore() override
    {
        m_value = m_prevValue;
    }

    QString getQString() override
    {
        return QString::number(m_value);
    }

    IValue& operator++() override
    {
        m_value++;
    }

    IValue& operator--() override
    {
        m_value--;
    }

private:
    TVar& m_value;
    TVar m_prevValue;

    TContext* m_context;
    bool (TContext::*m_setFunc) (TVar);
};

#endif // VALUE_H
