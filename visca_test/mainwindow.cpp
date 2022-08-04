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
        visca->executeCommand(ViscaControlCommands::Zoom::TeleVariable(7), 400, "Zooming");
    }

    if(event->key() == Qt::Key_Minus)
    {
        visca->executeCommand(ViscaControlCommands::Zoom::WideStandard(), 400, "Unzooming");
    }
}
