#include "iterable.h"

BoolIterable::BoolIterable(bool defaultState, QString trueText, QString falseText) :
    m_true(trueText), m_false(falseText)
{
    m_current = defaultState;
    m_marked = defaultState;
    m_default = defaultState;
}

void BoolIterable::next()
{
    m_current = !m_current;
}

void BoolIterable::prev()
{
    m_current = !m_current;
}

QString BoolIterable::text()
{
    return m_current ? m_true : m_false;
}

bool BoolIterable::get()
{
    return m_current;
}
