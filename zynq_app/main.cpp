#include "pipelines/ethernetPipeline.h"
#include "pipelines/rawFilePipeline.h"

#include <QCoreApplication>
#include <thread>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    EthernetPipeline ethernetPipeline;
    ethernetPipeline.start();

    // RawFilePipeline blocks...

    // std::thread rawPipelineThread([&](){
        RawFilePipeline rawFilePipeline;
        rawFilePipeline.start();
    // });

    // rawPipelineThread.join();

    gst_deinit();

    return a.exec();
}
