#include "mainwindow.h"

#include <QApplication>
#include "visible.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Visible video;

    return a.exec();
}
