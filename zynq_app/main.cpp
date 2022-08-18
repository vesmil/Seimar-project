#include <QApplication>

#include "library/gstreamer/gsfacade.h"
#include "library/visca/visca.h"
#include "global/config.h"
#include "graphic/mainWindow.h"

void nonEssentialSetup()
{
    qSetMessagePattern("(%{category}) %{function} - %{message}");
}

int main(int argc, char *argv[])
{
    nonEssentialSetup();

    QApplication a(argc, argv);

    // Setup gstreamer pipelines from cam
    // GsFacade gsFacade{};
    // gsFacade.initAndStart(GsFacade::RAW_RTP | GsFacade::RAW_DISPLAY);

    // Setup Visca protocol
    // Visca visca(glb::path::CAMERA_UART.c_str());

    // Create UI
    Menu &menu = Menu::getInstance();
    menu.show();

    return a.exec();
}
