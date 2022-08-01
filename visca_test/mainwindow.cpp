#include "mainwindow.h"

#include <QKeyEvent>

#include "global/logCategories.h"
#include "global/viscaConfig.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
{
    visca = new Visca(glb::visca::DEVICE_PATH);
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
