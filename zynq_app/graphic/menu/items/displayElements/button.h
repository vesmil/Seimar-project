#ifndef BUTTON_H
#define BUTTON_H

#include <QObject>
#include <QLabel>

// TODO where should set the bg color on change?
// I guess I should have two mehtods - on activation & on deactivation

class Button : public QLabel
{
    Q_OBJECT
public:

    Button();
};

#endif // BUTTON_H
