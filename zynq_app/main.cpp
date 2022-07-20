#include "pipeline.h"
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // TODO pipelines in separate thread

    // pipeline saving RAW video
    Pipeline pipeline;

    // pipeline for displaying video
    // ...

    return a.exec();
}
