#ifndef VALUESETELEMENT_H
#define VALUESETELEMENT_H

template <typename T>
class ValueSetElement
{
public:
    ValueSetElement();

    void execute() {}; // open popup I guess

private:
    T* value;
};

#endif // VALUESETELEMENT_H
