#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "library/visca/viscaCommunication.h"

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(driverUsb)


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

protected:
     void keyPressEvent(QKeyEvent *event) override;

private:
     ViscaCommunication* visca;
};

#endif // MAINWINDOW_H
