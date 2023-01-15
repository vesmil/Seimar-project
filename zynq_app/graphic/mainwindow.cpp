#include "mainwindow.h"

#include <graphic/menu/menu.h>

MainWindow::MainWindow()
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setStyleSheet("max-width: 350;");

    new QVBoxLayout(this);
    layout()->addWidget(&Menu::getInstance());
    Menu::getInstance().setVisible(false);
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    Menu::getInstance().keyPressEvent(event);
}
