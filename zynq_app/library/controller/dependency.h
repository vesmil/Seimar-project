#ifndef DEPENDENCY_H
#define DEPENDENCY_H

class IDependency {
public:
    virtual bool isValid() = 0;
};

template<typename TValue, typename TVar, TVar ...TPossible>
class Dependency : public IDependency
{
public:
    Dependency(TValue& value) : m_value(value) { }

    bool isValid() override
    {
        for (auto&& possibility : {TPossible...})
        {
            if (m_value.getValue() == possibility)
            {
                return true;
            }
        }

        return false;
    }

private:
    TValue& m_value;
};

#endif // DEPENDENCY_H
