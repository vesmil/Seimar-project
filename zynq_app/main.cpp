#include "raFilePipeline.h"

#include <QCoreApplication>
#include <thread>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::thread rawPipelineThread([&](){
        RawFilePipeline rawFilePipeline;
        rawFilePipeline.start_video();
        // stop_video() is temporarily in destructor of RawFilePipeline
    });

    // pipeline for displaying video
    // ...


    rawPipelineThread.join();

    return a.exec();
}
