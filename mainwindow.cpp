#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>
#include <QDebug>
#include "shortcircuit.h"
#include "drawing.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ConnectDevice_clicked()
{
    unsigned char* ReadBuf;

    if(usbOp->DevConnect() == 0)
    {
        usbOp->usb_send_read({ (unsigned char)0x97, (unsigned char)0x00 });

        usbOp->usb_send_read({ (unsigned char)0x18, (unsigned char)0xff });

        QThread::msleep(250);

//        usbOp->usb_send_read({ (unsigned char)0x18, (unsigned char)0xff });

//        QThread::msleep(250);

        ReadBuf = usbOp->usb_send_read({(unsigned char)0x9E,(unsigned char)0x01});
        QString str = (char*)ReadBuf;
        QString ProInfoStr = str.mid(11,16);
        ui->plainTextEdit->appendPlainText("固件版本号：" + ProInfoStr);
        QString SerialNoStr = str.mid(27,16);
        ui->plainTextEdit->appendPlainText("固件序列号：" + SerialNoStr);
    }
    else {
        ui->plainTextEdit->setPlainText("设备连接失败");
    }
}

void MainWindow::on_DataShow_clicked()
{
    ShortCircuit *shortCircuit = new ShortCircuit;
    shortCircuit->show();
}

void MainWindow::on_Drawing_clicked()
{
    Drawing *draw = new Drawing;
    draw->show();
}

void MainWindow::on_Reset_clicked()
{
    if(usbOp->DevConnect() == 0)
    {
        usbOp->usb_send_read({ (unsigned char)0x81, (unsigned char)0x80, (unsigned char)0x00 });
    }
    else {
        ui->plainTextEdit->appendPlainText("设备连接失败");
    }
}
