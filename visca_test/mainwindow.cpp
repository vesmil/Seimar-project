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
    //
    //  visca->inquireCommand<10>(ViscaCommands::Init::CAM_VersionInq(), ViscaCommands::Init::PrintVersionInfo);
    //  visca->inquireCommand(ViscaCommands::Exposure::Irirs::GetValue(), ViscaCommands::Exposure::Irirs::ValueFromReply);

    // No visible changes
    //  visca->executeCommand(ViscaCommands::Exposure::Gain::Change(ViscaCommands::ChangeEnum::RESET), 400, "res");
    //  visca->executeCommand(ViscaCommands::Exposure::Irirs::Change(ViscaCommands::UP), 1000, "up");


    if(event->key() == Qt::Key_Q)
    {
        visca->executeCommand(ViscaCommands::Zoom::setValue(0x2000));
        qCInfo(viscaLog()) << visca->inquireCommand(ViscaCommands::Zoom::getValue(), ViscaCommands::Zoom::valueFromReply, 400);
    }

    if(event->key() == Qt::Key_W)
    {
        visca->executeCommand(ViscaCommands::Focus::setValue(0xF000));
        qCInfo(viscaLog()) << visca->inquireCommand(ViscaCommands::Focus::getValue(), ViscaCommands::Focus::valueFromReply, 400);
    }

    if(event->key() == Qt::Key_E)
    {
        visca->executeCommand(ViscaCommands::Focus::setValue(0x0000));
        qCInfo(viscaLog()) << visca->inquireCommand(ViscaCommands::Focus::getValue(), ViscaCommands::Focus::valueFromReply, 400);
    }

    if(event->key() == Qt::Key_E)
    {
        visca->executeCommand(ViscaCommands::Focus::autoFocus(ViscaCommands::Focus::MANUAL));
    }

    if(event->key() == Qt::Key_T)
    {
        //visca->executeCommand(ViscaCommands::);
    }
}
