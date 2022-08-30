#include "mainWindow.h"
#include <QKeyEvent>
#include <QVBoxLayout>

#include "global/logcategories.h"
#include "graphic/menu/menu.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setCentralWidget(static_cast<QWidget*>(&Menu::getInstance()));
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    // Menu::getInstance().keyPressEvent(event);
}
