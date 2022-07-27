#include "gstreamer/gsFacade.h"

#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    GsFacade gsFacade;
    gsFacade.start(GsFacade::RAW | GsFacade::RTP);

    return a.exec();
}
