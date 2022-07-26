#include "pipelines/rtpPipeline.h"
#include "pipelines/rawFilePipeline.h"
#include "gsWrapper.h"

#include <QCoreApplication>
#include <thread>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    GstWrapper::init();

    // RawFilePipeline rawFilePipeline;
    // rawFilePipeline.start();

    RtpPipeline ethernetPipeline;
    ethernetPipeline.start();

    GstWrapper::deinit();

    return a.exec();
}
