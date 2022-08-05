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
    // Tested
    //  visca->executeCommand(ViscaCommands::Zoom::Direct(0x2000));
    //  visca->executeCommand(ViscaCommands::Zoom::TeleVariable(7), 400, "Zooming");
    //  visca->executeCommand(ViscaCommands::Zoom::WideStandard(), 400, "Unzooming");
    //  visca->executeCommand(ViscaCommands::Color::WhiteBalance::SetMode(ViscaCommands::Color::WhiteBalance::AUTO));

    // No visible changes
    //  visca->executeCommand(ViscaCommands::Exposure::Gain::Change(ViscaCommands::ChangeEnum::RESET), 400, "res");
    //  visca->executeCommand(ViscaCommands::Exposure::Irirs::Change(ViscaCommands::UP), 1000, "up");


    if(event->key() == Qt::Key_Q)
    {
        visca->executeCommandChecked(ViscaCommands::Exposure::Gain::Direct(0));
    }

    if(event->key() == Qt::Key_W)
    {
        visca->executeCommandChecked(ViscaCommands::Exposure::Gain::Direct(0x0C));
    }

    if(event->key() == Qt::Key_R)
    {
        visca->inquireCommand<10>(ViscaCommands::Init::CAM_VersionInq(), ViscaCommands::Init::PrintVersionInfo);
    }

    if(event->key() == Qt::Key_E)
    {
        //visca->executeCommand(ViscaCommands::);
    }

    if(event->key() == Qt::Key_T)
    {
        //visca->executeCommand(ViscaCommands::);
    }
}
