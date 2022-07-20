#include "pipeline.h"

#include <QCoreApplication>
#include <thread>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // pipeline saving RAW video
    Pipeline pipeline;

    std::thread rawPipeline([&](){
        pipeline.start_video();
    });

    rawPipeline.join();

    // pipeline for displaying video
    // ...

    return a.exec();
}
