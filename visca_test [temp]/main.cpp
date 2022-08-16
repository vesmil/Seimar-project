#include <QApplication>

#include "library/gstreamer/visible.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    qSetMessagePattern("(%{category}) %{function} - %{message}");

    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    Visible video;

    return a.exec();
}
