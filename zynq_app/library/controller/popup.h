#ifndef POPUP_H
#define POPUP_H

#include <QLabel>

//NOTE this needs to be more versatile

//! \brief QWidget with added controls
class ControlableWidget : public QLabel
{
public:
    ControlableWidget(const QString& text, QWidget* parentWidget);
    void control(QKeyEvent* event);
};

#endif // POPUP_H
