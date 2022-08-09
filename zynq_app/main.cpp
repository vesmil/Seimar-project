#include <QCoreApplication>
#include "library/gstreamer/gsFacade.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Setup gstreamer pipelines from cam
    GsFacade gsFacade;
    gsFacade.initAndStart(GsFacade::RTP); // | GsFacade::RAW | ...

    // Setup Visca protocol
    // TODO

    // Create UI

    return a.exec();
}
