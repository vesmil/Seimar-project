#include "mainwindow.h"

#include "visca.h"

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
        visca->zoomTele(10);
    }
}
