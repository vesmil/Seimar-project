#ifndef POPUP_H
#define POPUP_H

#include <QLabel>

class ControlableWidget : public QLabel
{
public:
    ControlableWidget(const QString& text, QWidget* parentWidget);

    void control(QKeyEvent* event);
};

#endif // POPUP_H
