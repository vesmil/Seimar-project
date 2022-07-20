#include "pipeline.h"
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Pipeline pipeline;
    return a.exec();
}
