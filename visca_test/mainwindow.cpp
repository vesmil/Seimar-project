#include "mainwindow.h"

#include <QKeyEvent>
#include "global/logCategories.h"

Q_LOGGING_CATEGORY(driverUsb, "driver.usb")


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
{
    visca = new ViscaCommunication;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_R)
    {
        visca->zoomTeleStandard();
    }

    if(event->key() == Qt::Key_T)
    {
        visca->zoomWideStandard();
    }
}
