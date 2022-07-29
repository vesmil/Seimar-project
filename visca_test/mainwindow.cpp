#include "mainwindow.h"

#include <QKeyEvent>
#include "global/logCategories.h"

Q_LOGGING_CATEGORY(driverUsb, "driver.usb")


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
{
    visca = new Visca;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_R)
    {
        qInfo() << "R pressed";

        // visca->zoomTele(10);
    }
}
