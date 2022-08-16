#include "mainwindow.h"

#include <QKeyEvent>

#include "../zynq_app/global/logCategories.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
{
    visca = new Visca("/dev/ttymxc4");
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    // visca->inquireCommand(ViscaCommands::Init::getVersionInfo(), ViscaCommands::Init::printVersionInfo);


    switch(event->key())
    {
        case Qt::Key_Q:
            visca->executeCommand(ViscaCommands::horizontalFlip(ViscaCommands::OFF));
            break;

        case Qt::Key_W:
            visca->executeCommand(ViscaCommands::Exposure::setMode(ViscaCommands::Exposure::Mode::IRIS_PRI));
            break;

        case Qt::Key_E:
            visca->executeCommand(ViscaCommands::Exposure::Iris::change(ViscaCommands::UP));
            break;

        case Qt::Key_R:
            visca->executeCommand(ViscaCommands::Exposure::Iris::change(ViscaCommands::DOWN));
            break;

        case Qt::Key_T:
            visca->executeCommand(ViscaCommands::Exposure::Iris::setValue(0x05));
            break;

        case Qt::Key_Y:
            visca->executeCommand(ViscaCommands::Exposure::Iris::setValue(0x15));
            break;

        case Qt::Key_U:
            qCInfo(viscaLog()) << visca->inquireCommand(ViscaCommands::Exposure::Iris::getValue(), ViscaCommands::Exposure::Iris::valueFromReply);
            break;

        case Qt::Key_I:
            break;

        case Qt::Key_O:
            break;

        case Qt::Key_P:
            break;

        case Qt::Key_A:
            break;

        case Qt::Key_S:
            break;

        case Qt::Key_D:
            break;

        case Qt::Key_F:
            break;

    }
}
