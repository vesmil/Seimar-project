#ifndef POPUP_H
#define POPUP_H

#include <QLabel>

//! \brief Interface for a displayable value
class IControlablePopup
{
public:
    virtual void open() = 0;
    virtual void close() = 0;

    virtual void control(QKeyEvent* event) = 0;
    virtual QWidget* getWidget();
};

#endif // POPUP_H
