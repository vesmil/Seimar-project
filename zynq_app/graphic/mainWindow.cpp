#include "mainWindow.h"
#include <QKeyEvent>
#include <QVBoxLayout>

#include "global/logCategories.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), menu(this)
{
    setCentralWidget(&menu);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    menu.keyPressEvent(event);
}
