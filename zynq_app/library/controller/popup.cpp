#include "popup.h"


ControlableWidget::ControlableWidget(const QString& text, QWidget* parentWidget) : QLabel(text, parentWidget)
{
}

void ControlableWidget::control(QKeyEvent* event)
{

}
