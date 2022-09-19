#ifndef VALUE_H
#define VALUE_H

#include <QString>
#include <array>
#include <vector>

#include "library/controller/controllercommand.h"
#include "graphic/menu/items/ivalue.h"
#include "library/controller/dependency.h"

// TODO remove need for

/*!
 * \brief Class that represents a value (in menu) and after change it calls a function
 * @tparam TValue Type of value
 * @tparam TParam Type to which TValue is converted before calling confirmation function
 * @tparam TContext Context in which confirmation function is called
 */
template<typename TValue, typename TParam, typename TContext>
class ValueSetter : public IValueSetter
{
public:
    ValueSetter(TValue defaultValue, TValue minValue, TValue maxValue, bool (TContext::*setFunc) (TParam), TContext* context, QString units = "")
        : m_value(defaultValue),
          m_units(units),
          m_default(m_value),
          m_min(minValue),
          m_max(maxValue),
          m_controller(context),
          m_setFunc(setFunc)
    {
    }

    virtual TParam getValue()
    {
        return static_cast<TParam>(m_value);
    }

    void setAsync() override
    {
        m_controller->addCommandToQueue(makeCommand(m_setFunc, m_controller, getValue()));
    }

    void set() override
    {
        (m_controller->*m_setFunc)(getValue());
    }

    void setDefault() override
    {
        m_value = m_default;
        set();
    }

    void restorePrev() override
    {
        m_value = m_prevValue;
    }

    bool hasChanged() override
    {
        return m_prevValue != m_value;
    }

    void store() override
    {
        m_prevValue = TValue(m_value);
    }

    QString getQString() override
    {
        return QString::number(m_value) + m_units;
    }

    void operator++() override
    {
        if(m_value < m_max)
        {
            m_value = static_cast<TValue>(m_value + 1);
        }
        else
        {
            m_value = m_min;
        }
    }

    void operator--() override
    {
        if(m_value > m_min)
        {
            m_value = static_cast<TValue>(m_value - 1);
        }
        else
        {
            m_value = m_max;
        }
    }

    void addDependency(IDependency* dependency)
    {
        m_dependencies.emplace_back(dependency);
    }

    bool isHidden() override
    {
        for (auto& dependency : m_dependencies)
        {
            if (!dependency->isValid())
            {
                return true;
            }
        }

        return false;
    }

protected:
    TValue m_value;
    QString m_units;

    TValue m_default;
    TValue m_min;
    TValue m_max;

    TValue m_prevValue;

    TContext* m_controller;
    bool (TContext::*m_setFunc) (TParam);

    std::vector<IDependency*> m_dependencies {};
};

// TODO delete BoolValue and ArrValue using iterator

template<typename TContext>
class BoolValue : public ValueSetter<bool, bool, TContext>
{
public:
    BoolValue(bool defaultVal, bool (TContext::*setFunc) (bool), TContext* context, QString trueMessage = "On", QString falseMessage = "Off")
        : ValueSetter<bool, bool, TContext>(defaultVal, false, true, setFunc, context, ""),
          m_onString(trueMessage), m_offString(falseMessage)
    {
    }

    QString getQString() override
    {
        return this->m_value ? m_onString : m_offString;
    }

    void operator++() override
    {
        this->m_value = !this->m_value;
    }

    void operator--() override
    {
        this->m_value = !this->m_value;
    }

private:
    QString m_onString;
    QString m_offString;
};

template<typename TParam, typename TContext, std::size_t TSize>
class ArrValue : public ValueSetter<std::size_t, TParam, TContext>
{
public:
    ArrValue(const std::array<std::pair<TParam, QString>, TSize> *array, bool (TContext::*setFunc) (TParam), TContext* context)
        : ValueSetter<std::size_t, TParam,TContext>(0U, 0U, TSize - 1, setFunc, context), m_array(array)
    {
    }

    QString getQString() override
    {
        return m_array->at(this->m_value).second;
    }

    TParam getValue() override
    {
        return m_array->at(this->m_value).first;
    }

private:
    const std::array<std::pair<TParam, QString>, TSize> *m_array;
};

#endif // VALUE_H
