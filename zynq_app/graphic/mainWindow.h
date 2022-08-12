#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "menu/menu.h"

// Not sure if gonna be used or menu will go straight to the mixer...

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

private slots:

private:
    void keyPressEvent(QKeyEvent *event);

    Menu menu{this};
};
#endif // MAINWINDOW_H
