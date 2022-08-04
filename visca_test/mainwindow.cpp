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
    // Switch for larger testing...

    if(event->key() == Qt::Key_Plus)
    {
        visca->executeCommand(ViscaCommands::Zoom::TeleVariable(7), 400, "Zooming");
    }
    else if(event->key() == Qt::Key_Minus)
    {
        visca->executeCommand(ViscaCommands::Zoom::WideStandard(), 400, "Unzooming");
    }
    else if(event->key() == Qt::Key_Enter)
    {
        visca->executeCommand(ViscaCommands::Zoom::Direct(0x2000));
    }

    if(event->key() == Qt::Key_W)
    {
        visca->executeCommand(ViscaCommands::Exposure::Gain::Change(ViscaCommands::ChangeEnum::RESET), 400, "res");
    }

    if(event->key() == Qt::Key_T)
    {
        visca->executeCommand(ViscaCommands::Color::WhiteBalance::SetMode(ViscaCommands::Color::WhiteBalance::AUTO));
    }
}
