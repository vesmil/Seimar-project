#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow();

    void keyPressEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_H
