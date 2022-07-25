#include "pipelines/ethernetPipeline.h"
#include "pipelines/rawFilePipeline.h"

#include <QCoreApplication>
#include <thread>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    /*
    std::thread rawPipelineThread([&](){
        RawFilePipeline rawFilePipeline;
        rawFilePipeline.start_video();
        // stop_video() is temporarily in destructor of RawFilePipeline
    });
    */

    // pipeline for displaying video
    // std::thread ethernetPipelineThread([&](){

    EthernetPipeline ethernetPipeline;
    ethernetPipeline.start();

    // });

    // ethernetPipelineThread.join();

    return a.exec();
}
