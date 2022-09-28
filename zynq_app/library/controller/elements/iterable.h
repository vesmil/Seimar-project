#ifndef ITERABLE_H
#define ITERABLE_H

#include <QString>

/*!
 * \brief Abstract class that allows iteration over some set of elements
 */
template<typename T>
class Iterable
{
public:
    virtual void next() = 0;
    virtual void prev() = 0;
    virtual QString text() = 0;

    virtual void setDefault()
    {
        m_current = m_default;
    }

    virtual void setMarked()
    {
        m_current = m_marked;
    }

    virtual void mark()
    {
        m_marked = m_current;
    }

    virtual bool diffFromMarked()
    {
        return m_marked == m_current;
    }

    virtual T get()
    {
        return m_current;
    }

protected:
    T m_current;
    T m_default;
    T m_marked;
};


/*!
 * \brief For iteration over bool - it's possible to specify custom text for each state
 */
class BoolIterable : public Iterable<bool>
{
public:
    BoolIterable(bool defaultState, QString trueText="On", QString falseText="Off");

    void next() override;
    void prev() override;

    QString text() override;
    bool get() override;

private:
    QString m_true;
    QString m_false;
};


/*!
 * \brief For iteration over array of pairs with element and QString to represent the element
 */
template<typename TElem, size_t TSize>
class PairArrayIterable : public Iterable<TElem>{
public:
    PairArrayIterable(const std::array<std::pair<TElem, QString>, TSize>& array) : m_array(array) {}

    void next()
    {
        m_current = (m_current == TSize - 1) ? 0 : m_current + 1;
    }

    void prev()
    {
        m_current = (m_current == 0u) ? TSize - 1 : m_current - 1;
    }

    void setDefault() override
    {
        m_current = m_default;
    }

    void setMarked() override
    {
        m_current = m_marked;
    }

    void mark() override
    {
        m_marked = m_current;
    }

    bool diffFromMarked() override
    {
        return m_marked == m_current;
    }

    QString text()
    {
        return m_array.at(m_current).second;
    }

    TElem get()
    {
        return m_array.at(m_current).first;
    }

private:
    const std::array<std::pair<TElem, QString>, TSize>& m_array;

    size_t m_current = 0;
    size_t m_default = 0;
    size_t m_marked = 0;
};


/*!
 * \brief For iteration over range of integer values
 */
template<typename T, class = typename std::enable_if<std::is_integral<T>::value>::type>
class ValueIterable : public Iterable<T>
{
public:
    ValueIterable(T defaultVal, T minVal, T maxVal) : m_min(minVal), m_max(maxVal)
    {
        this->m_current = defaultVal;
        this->m_marked = defaultVal;
        this->m_default = defaultVal;
    }

    void next() override
    {
        this->m_current = (this->m_current == m_max) ? 0 : this->m_current + 1;
    }

    void prev()
    {
        this->m_current = (this->m_current == 0) ? m_max : this->m_current - 1;
    }

    QString text() override
    {
        return QString::number(this->m_current);
    }

    T get()
    {
        return this->m_current;
    }

private:
    T m_min;
    T m_max;
};

#endif // ITERABLE_H
