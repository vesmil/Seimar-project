#include <QGuiApplication>

#include "library/gstreamer/gsFacade.h"
#include "library/visca/visca.h"
#include "global/config.h"

#include "graphic/mainWindow.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Setup gstreamer pipelines from cam
    GsFacade gsFacade{};
    gsFacade.initAndStart(GsFacade::RAW_RTP | GsFacade::RAW_DISPLAY);

    // Setup Visca protocol
    // Visca visca(glb::path::CAMERA_UART.c_str());

    // Create UI
    // MainWindow window;
    // window.show();

    return a.exec();
}
