#include <QCoreApplication>
#include "gstreamer/gsFacade.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    GsFacade gsFacade;
    gsFacade.initAndStart(GsFacade::RAW | GsFacade::RTP);

    return a.exec();
}
