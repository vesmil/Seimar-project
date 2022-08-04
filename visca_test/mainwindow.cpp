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
        visca->executeCommand(ViscaCommands::Zoom::TeleVariable(7), 400, "Zooming");
    }

    if(event->key() == Qt::Key_Minus)
    {
        visca->executeCommand(ViscaCommands::Zoom::WideStandard(), 400, "Unzooming");
    }


    if(event->key() == Qt::Key_Q)
    {
        visca->executeCommand(ViscaCommands::Zoom::Direct(0x4000));
    }

    if(event->key() == Qt::Key_W)
    {
        visca->executeCommand(ViscaCommands::Exposure::Gain::Change(ViscaCommands::ChangeEnum::RESET), 400, "res");
    }

    if(event->key() == Qt::Key_R)
    {
        visca->executeCommand(ViscaCommands::Exposure::Gain::Change(ViscaCommands::ChangeEnum::UP), 400, "up");
    }

    if(event->key() == Qt::Key_T)
    {
        visca->executeCommand(ViscaCommands::Color::WhiteBalance::SetMode(ViscaCommands::Color::WhiteBalance::AUTO));
    }
}
