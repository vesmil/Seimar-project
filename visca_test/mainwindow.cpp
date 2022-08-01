#include "mainwindow.h"

#include <QKeyEvent>

#include "global/logCategories.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
{
    visca = new Visca("/dev/ttymxc4");
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Plus)
    {
        visca->zoomTeleStandard();
    }

    if(event->key() == Qt::Key_Minus)
    {
        visca->zoomWideStandard();
    }
}
