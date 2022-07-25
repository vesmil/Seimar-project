#include "pipelines/ethernetPipeline.h"
#include "pipelines/rawFilePipeline.h"

#include <QCoreApplication>
#include <thread>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    EthernetPipeline ethernetPipeline;
    ethernetPipeline.start();

    RawFilePipeline rawFilePipeline;
    rawFilePipeline.start();

    gst_deinit();

    return a.exec();
}
