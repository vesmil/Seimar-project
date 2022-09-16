#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

//! \note It won't be used in final version as we will use video mixer (to merge video from camera and UI)
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

private slots:

private:
    void keyPressEvent(QKeyEvent *event);
};
#endif // MAINWINDOW_H
