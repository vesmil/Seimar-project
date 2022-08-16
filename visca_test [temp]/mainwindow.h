#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../zynq_app/library/visca/visca.h"

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
     Visca* visca;
};

#endif // MAINWINDOW_H
