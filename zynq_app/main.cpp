#include <QCoreApplication>

#include "library/gstreamer/gsFacade.h"
#include "library/visca/visca.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Setup gstreamer pipelines from cam
    GsFacade gsFacade{};
    gsFacade.initAndStart(GsFacade::RTP); // | GsFacade::RAW | ...

    // Setup Vi\sca protocol
    Visca visca("...");

    // Create UI
    // TODO

    return a.exec();
}
