#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "usboperation.h"
#include "enlarge.h"

using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_ConnectDevice_clicked();
    void on_DataShow_clicked();
    void on_Drawing_clicked();

    void on_Reset_clicked();

private:
    Ui::MainWindow *ui;

    UsbOperation *usbOp;
};

#endif // MAINWINDOW_H
