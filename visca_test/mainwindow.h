#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QWidget>
#include <QKeyEvent>
#include <QDebug>

#include "visca.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

protected:
     void keyPressEvent(QKeyEvent *event) override;

private:
     Visca* visca;
};

#endif // MAINWINDOW_H
