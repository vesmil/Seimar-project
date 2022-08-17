#ifndef VALUESETTER_H
#define VALUESETTER_H

#include <QObject>
#include <QWidget>
#include <QLineEdit>

// TODO not really I guess - problems with using keyboard only
// solve it by QLabel? With pointer to val?
class valueSetter : public QLineEdit
{
    Q_OBJECT
public:
    valueSetter();

    enum type { TEXT, TEXT_ARROWS };

    // TODO ...
    // TODO limits
};

#endif // VALUESETTER_H
