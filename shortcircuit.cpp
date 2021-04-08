#include "shortcircuit.h"
#include "ui_shortcircuit.h"
#include <QThread>
#include <QDebug>
#include <QDir>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QDesktopWidget>

unsigned char pgbuf3[15000];
unsigned char pgbuf1[15000];
unsigned char pgbuf2[15000];
unsigned char pgbuf4[15000];
unsigned char p3[15000];
unsigned char p1[15000];
unsigned char p2[15000];
unsigned char p4[15000];
int ColumnCount = 10,RowCount = 10;
int InDataFlag = 0;
int enlargeNum = 0;

ShortCircuit::ShortCircuit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShortCircuit)
{
    ui->setupUi(this);
    ui->CalibrationData->hide();
    ui->ShortTest->hide();
    ui->OpenTest->hide();
    ui->FlatnessTest->hide();
    ui->OutData->hide();
    QDesktopWidget* pDesktopWidget = QApplication::desktop();
    QRect screenRect = pDesktopWidget->screenGeometry();
    resize(screenRect.width(),screenRect.height() - 100);
}

ShortCircuit::~ShortCircuit()
{
    delete ui;
}

void ShortCircuit::GetRowColumn()
{
    unsigned char* ReadBuf;

    if(usbOpera->DevConnect() == 0)
    {
        usbOpera->usb_send_read({ (unsigned char)0x97, (unsigned char)0x00 });
        usbOpera->usb_send_read({ (unsigned char)0x18, (unsigned char)0xff });
        QThread::msleep(250);

        ReadBuf = usbOpera->usb_send_read({(unsigned char)0x33});
        ColumnCount = ReadBuf[4];
        RowCount = ReadBuf[3];
    }
    else {
        ui->plainTextEdit->appendPlainText("设备连接失败");
    }
    MakingTables(ColumnCount, RowCount);
    qDebug() << RowCount << ColumnCount;
}

void ShortCircuit::MakingTables(int ColumnCount, int RowCount)
{
    standItemModel = new QStandardItemModel;
    standItemModel->setColumnCount(ColumnCount);
    standItemModel->setRowCount(RowCount);
    ui->tableView->setModel(standItemModel);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    for(int i = 0; i < ColumnCount; i++){
        ui->tableView->setColumnWidth(i,25);
    }
    for(int i = 0; i < RowCount; i++){
        ui->tableView->setRowHeight(i,25);
    }

    ui->tableView->setFont(QFont("song", 6));
    ui->tableView->horizontalHeader()->setFont(QFont("song",6));
    ui->tableView->horizontalHeader()->setMaximumHeight(25);
}

bool ShortCircuit::saveBinaryFile(QString &aFileName)
{//保存为纯二进制文件
    QFile aFile(aFileName);  //以文件方式读出
    if (!(aFile.open(QIODevice::WriteOnly)))
        return false;
    QDataStream aStream(&aFile); //用文本流读取文件
    aStream.setByteOrder(QDataStream::LittleEndian);//windows平台

    qint16 aRowCount = standItemModel->rowCount();
    aStream << aRowCount;
    qint16 aColumnCount = standItemModel->columnCount();
    aStream << aColumnCount;

    int a = 0;
    for(int j = 0; j < aRowCount*aColumnCount;j ++)
    {
        QString str = QString(pgbuf3[a]);
        a++;
        QByteArray mbyte = str.toUtf8();
        qint16 num;
        for(int b=0;b<mbyte.size();b++)
        {
            num = mbyte.at(b) & 0xFF;
        }
        aStream << num;
    }

    a = 0;
    for(int j = 0; j < aRowCount*aColumnCount;j ++)
    {
        QString str = QString(pgbuf1[a]);
        a++;
        QByteArray mbyte = str.toUtf8();
        qint16 num;
        for(int b=0;b<mbyte.size();b++)
        {
            num = mbyte.at(b) & 0xFF;
        }
        aStream << num;
    }

    a = 0;
    for(int j = 0; j < aRowCount*aColumnCount;j ++)
    {
        QString str = QString(pgbuf2[a]);
        a++;
        QByteArray mbyte = str.toUtf8();
        qint16 num;
        for(int b=0;b<mbyte.size();b++)
        {
            num = mbyte.at(b) & 0xFF;
        }
        aStream << num;
    }

    a = 0;
    for(int j = 0; j < aRowCount*aColumnCount;j ++)
    {
        QString str = QString(pgbuf4[a]);
        a++;
        QByteArray mbyte = str.toUtf8();
        qint16 num;
        for(int b=0;b<mbyte.size();b++)
        {
            num = mbyte.at(b) & 0xFF;
        }
        aStream << num;
    }

    aFile.close();
    return true;
}

bool ShortCircuit::openBinaryFile(QString &aFileName)
{
    MakingTables(RowCount, ColumnCount);
    InDataFlag = 1;
    //打开二进制文件
    QFile aFile(aFileName);  //以文件方式读出
    if (!(aFile.open(QIODevice::ReadOnly)))
        return false;
    QDataStream aStream(&aFile); //用文本流读取文件
    aStream.setByteOrder(QDataStream::LittleEndian);

    qint16 str;
    aStream >> str;
    int aRowCount = str;
    qDebug() << aRowCount;
    aStream >> str;
    int aColumnCount = str;
    qDebug() << aColumnCount;

    memset(p3, 0xFFFF, 15000);
    int a = 0;
    for(int j = 0; j < aRowCount*aColumnCount;j ++)
    {
        aStream >> str;
        p3[a] = str;
        qDebug() << p3[a];
        a++;
    }

    memset(p1, 0xFFFF, 15000);
    a = 0;
    for(int j = 0; j < aRowCount*aColumnCount;j ++)
    {
        aStream >> str;
        p1[a] = str;
        a++;
    }

    memset(p2, 0xFFFF, 15000);
    a = 0;
    for(int j = 0; j < aRowCount*aColumnCount;j ++)
    {
        aStream >> str;
        p2[a] = str;
        a++;
    }

    memset(p4, 0xFFFF, 15000);
    a = 0;
    for(int j = 0; j < aRowCount*aColumnCount;j ++)
    {
        aStream >> str;
        p4[a] = str;
        a++;
    }

    RowCount = aRowCount;
    ColumnCount = aColumnCount;
    resetTable(aRowCount, aColumnCount);
    aFile.close();
    return true;
}

void ShortCircuit::resetTable(int aRowCount, int aColumnCount)
{
    standItemModel->removeRows(0,standItemModel->rowCount()); //删除所有行
    standItemModel->setRowCount(aRowCount);//设置新的行数
    standItemModel->removeColumns(0, standItemModel->columnCount());
    standItemModel->setColumnCount(aColumnCount);

    for(int i = 0; i < aColumnCount; i++){
        ui->tableView->setColumnWidth(i,20);
    }
    for(int i = 0; i < aRowCount; i++){
        ui->tableView->setRowHeight(i,20);
    }
}

void ShortCircuit::on_CalibrationData_clicked()
{
    QStandardItem *aItem;
    int a = 0;
    for(int i=0;i<RowCount;i++)
    {
        for(int j = 0; j < ColumnCount; j++)
        {
            QString str;
            if(InDataFlag == 1)
            {
                str = QString(p3[a]);
            }
            else {
                str = QString(pgbuf3[a]);
            }
            a++;
            QByteArray mbyte = str.toUtf8();
            int num;
            for(int b=0;b<mbyte.size();b++)
            {
                num = mbyte.at(b) & 0xFF;
            }
            QString ToStr = QString::number(num,10);
            aItem=new QStandardItem(ToStr);//创建item
            standItemModel->setItem(i,j,aItem);
            if(num < 118 || num > 138)
            {
                standItemModel->setData(standItemModel->index(i,j),QBrush(Qt::yellow),Qt::BackgroundColorRole);
            }
        }
    }
}

void ShortCircuit::on_OutData_clicked()
{//保存二进制文件
    QString curPath=QDir::currentPath();
    //调用打开文件对话框选择一个文件
//    QString aFileName=QFileDialog::getSaveFileName(this,tr("保存文件"),curPath,"*.dat");
    QString aFileName = QString(curPath + "/outdata.stm");
    if (aFileName.isEmpty())
    {
        return;
    }

    if  (saveBinaryFile(aFileName)) //保存为流数据文件
    {
//        QMessageBox::information(this,"提示消息","文件已经成功保存!");
    }
}

void ShortCircuit::on_InData_clicked()
{
    QString curPath=QDir::currentPath();
    //调用打开文件对话框打开一个文件
    QString aFileName=QFileDialog::getOpenFileName(this,tr("打开文件"),curPath,"*.stm");
    if(aFileName.isEmpty())
    {
        return;
    }
    if(openBinaryFile(aFileName)) //保存为流数据文件
    {
        QMessageBox::information(this,"提示消息","文件已经打开!");
    }
}

void ShortCircuit::on_ShortTest_clicked()
{
    QStandardItem *aItem;
    int a = 0;
    for(int i=0;i<RowCount;i++)
    {
        for(int j = 0; j < ColumnCount; j++)
        {
            QString str;
            if(InDataFlag == 1)
            {
                str = QString(p1[a]);
            }
            else {
                str = QString(pgbuf1[a]);
            }
            a++;
            QByteArray mbyte = str.toUtf8();
            int num;
            for(int b=0;b<mbyte.size();b++)
            {
                num = mbyte.at(b) & 0xFF;
            }
            if(num < 20 || num > 235)
            {
                QString ToStr = QString::number(num,10);
                aItem=new QStandardItem(ToStr);//创建item
                standItemModel->setItem(i,j,aItem);
                standItemModel->setData(standItemModel->index(i,j),QBrush(Qt::red),Qt::BackgroundColorRole);
            }
            else {
                QString ToStr = QString::number(num,10);
                aItem=new QStandardItem(ToStr);//创建item
                standItemModel->setItem(i,j,aItem);
                if(num < 112 || num > 144)
                {
                    standItemModel->setData(standItemModel->index(i,j),QBrush(Qt::yellow),Qt::BackgroundColorRole);
                }
            }
        }
    }
}

void ShortCircuit::on_OpenTest_clicked()
{
    QStandardItem *aItem;
    int a = 0;
    for(int i=0;i<RowCount;i++)
    {
        for(int j = 0; j < ColumnCount; j++)
        {
            QString str;
            if(InDataFlag == 1)
            {
                str = QString(p2[a]);
            }
            else {
                str = QString(pgbuf2[a]);
            }
            a++;
            QByteArray mbyte = str.toUtf8();
            int num;
            for(int b=0;b<mbyte.size();b++)
            {
                num = mbyte.at(b) & 0xFF;
            }
            if(num < 100)
            {
                QString ToStr = QString::number(num,10);
                aItem=new QStandardItem(ToStr);//创建item
                standItemModel->setItem(i,j,aItem);
                if(num < 20){
                    standItemModel->setData(standItemModel->index(i,j),QBrush(Qt::red),Qt::BackgroundColorRole);
                }
                else {
                    standItemModel->setData(standItemModel->index(i,j),QBrush(Qt::yellow),Qt::BackgroundColorRole);
                }
            }
            else {
                QString ToStr = QString::number(num,10);
                aItem=new QStandardItem(ToStr);//创建item
                standItemModel->setItem(i,j,aItem);
            }
        }
    }
}

void ShortCircuit::on_FlatnessTest_clicked()
{
    QStandardItem *aItem;
    int a = 0;
    for(int i=0;i<RowCount;i++)
    {
        for(int j = 0; j < ColumnCount; j++)
        {
            QString str;
            if(InDataFlag == 1)
            {
                str = QString(p4[a]);
            }
            else {
                str = QString(pgbuf4[a]);
            }
            a++;
            QByteArray mbyte = str.toUtf8();
            int num;
            for(int b=0;b<mbyte.size();b++)
            {
                num = mbyte.at(b) & 0xFF;
            }
            QString ToStr = QString::number(num,10);
            aItem=new QStandardItem(ToStr);//创建item
            standItemModel->setItem(i,j,aItem);
            if(num < 118 || num > 138)
            {
                standItemModel->setData(standItemModel->index(i,j),QBrush(Qt::yellow),Qt::BackgroundColorRole);
            }
        }
    }
}

void ShortCircuit::on_StartTest_clicked()
{
    GetRowColumn();
    ui->StartTest->setEnabled(false);
    if(usbOpera->DevConnect() == 0)
    {
        usbOpera->usb_send_read({ (unsigned char)0x97, (unsigned char)0x00 });
        usbOpera->usb_send_read({ (unsigned char)0x18, (unsigned char)0xff });
        QThread::msleep(250);

        InDataFlag = 0;
        ui->plainTextEdit->setPlainText("读取校准数据...");
        memset(pgbuf3, 0xFFFF, 15000);
        usbOpera->usb_send({ (unsigned char)0x18, (unsigned char)0x09 });//读取校准数据
        usbOpera->usb_read_page(&pgbuf3[0]);
        usbOpera->usb_send_read({ (unsigned char)0x18, (unsigned char)0xff });
        ui->progressBar->setValue(25);
        QThread::msleep(250);
        int res = usbOpera->clearUsb();
        while (res == 1) {
            res = usbOpera->clearUsb();
            QThread::msleep(10);
        }

        ui->plainTextEdit->appendPlainText("获取短路测试数据...");
        memset(pgbuf1, 0xFFFF, 15000);
        usbOpera->usb_send({ (unsigned char)0x98, (unsigned char)0xF1 });
        usbOpera->usb_send({ (unsigned char)0x99, (unsigned char)0x03 });//短路测试
        usbOpera->usb_read_page(&pgbuf1[0]);
        usbOpera->usb_send_read({ (unsigned char)0x18, (unsigned char)0xff });
        ui->progressBar->setValue(50);
        ShortError();
        QThread::msleep(250);

        ui->plainTextEdit->appendPlainText("获取开路测试数据...");
        memset(pgbuf2, 0xFFFF, 15000);
        usbOpera->usb_send({ (unsigned char)0x99, (unsigned char)0x02 });//开路测试
        usbOpera->usb_read_page(&pgbuf2[0]);
        usbOpera->usb_send_read({ (unsigned char)0x18, (unsigned char)0xff });
        ui->progressBar->setValue(75);
        OpenError();
        QThread::msleep(250);

        ui->plainTextEdit->appendPlainText("获取平整度测试数据...");
        memset(pgbuf4, 0xFFFF, 15000);
        usbOpera->usb_send({ (unsigned char)0x98, (unsigned char)0x10 });
        usbOpera->usb_send({ (unsigned char)0x99, (unsigned char)0x00 });//平整度测试
        usbOpera->usb_read_page(&pgbuf4[0]);
        usbOpera->usb_send_read({ (unsigned char)0x18, (unsigned char)0xff });
        ui->progressBar->setValue(100);
        QThread::msleep(250);

        ui->StartTest->setEnabled(true);

        on_OutData_clicked();
        usbOpera->usb_send_read({ (unsigned char)0x81, (unsigned char)0x80, (unsigned char)0x00 });
        ui->plainTextEdit->appendPlainText("数据测试完成");
    }
    else {
        ui->StartTest->setEnabled(true);
        ui->plainTextEdit->appendPlainText("设备连接失败");
    }
}

void ShortCircuit::ShortError()
{
    ui->plainTextEdit_2->clear();
    ui->plainTextEdit_2->appendPlainText("TP短路异常:");
    ui->plainTextEdit_2->appendPlainText("Tx:");
    int a = ColumnCount - 1;
    for(int i = 0; i < (RowCount - 2); i++)
    {
        QString str = QString(pgbuf1[a]);
        a += ColumnCount;
        QByteArray mbyte = str.toUtf8();
        int num;
        for(int b=0;b<mbyte.size();b++)
        {
            num = mbyte.at(b) & 0xFF;
        }
        if(num < 50 || num > 200)
        {
            ui->plainTextEdit_2->insertPlainText(QString::asprintf("%d ",i+1));
        }
    }

    ui->plainTextEdit_2->appendPlainText("Rx:");
    int b = (RowCount - 1) * ColumnCount;
    for(int i = 0; i < (ColumnCount - 1); i++)
    {
        QString str = QString(pgbuf1[b]);
        b ++;
        QByteArray mbyte = str.toUtf8();
        int num;
        for(int a=0;a<mbyte.size();a++)
        {
            num = mbyte.at(a) & 0xFF;
        }
        if(num < 50 || num > 200)
        {
            ui->plainTextEdit_2->insertPlainText(QString::asprintf("%d ",i+1));
        }
    }
}

void ShortCircuit::OpenError()
{
    ui->plainTextEdit_2->appendPlainText("TP开路异常:");
    ui->plainTextEdit_2->appendPlainText("Tx:");
    int a = 0;
    for(int i = 0; i < RowCount - 1; i++)
    {
        int ErrorCount = 0;
        for(int j = 0; j < ColumnCount; j++)
        {
            QString str = QString(pgbuf2[a]);
            a ++;
            QByteArray mbyte = str.toUtf8();
            int num;
            for(int b=0;b<mbyte.size();b++)
            {
                num = mbyte.at(b) & 0xFF;
            }
            if(num < 20)
            {
                ErrorCount ++;
                if(ErrorCount >= ColumnCount)
                {
                    ui->plainTextEdit_2->insertPlainText(QString::asprintf("%d ",i+1));
                }
            }
        }
    }

    ui->plainTextEdit_2->appendPlainText("Rx:");
    int b = 0,keepb = 0;
    for(int i = 0; i < ColumnCount; i++)
    {
        b = keepb;
        int ErrorCount = 0;
        for(int j = 0; j < RowCount - 2; j++)
        {
            QString str = QString(pgbuf2[b]);
            b += ColumnCount;
            QByteArray mbyte = str.toUtf8();
            int num;
            for(int a=0;a<mbyte.size();a++)
            {
                num = mbyte.at(a) & 0xFF;
            }
            if(num < 20)
            {
                ErrorCount ++;
                if(ErrorCount >= (RowCount - 2))
                {
                    ui->plainTextEdit_2->insertPlainText(QString::asprintf("%d ",i+1));
                }
            }
        }
        keepb ++;
    }
}

void ShortCircuit::keyPressEvent(QKeyEvent *e)
{
    if(e->modifiers() == Qt::AltModifier && e->key() == Qt::Key_S)
    {
        ui->CalibrationData->show();
        ui->FlatnessTest->show();
        ui->ShortTest->show();
        ui->OpenTest->show();
    }
}

void ShortCircuit::on_Enlarge_clicked()
{
    enlargeNum++;
    Enlarge = new enlarge(this);
    Enlarge->show();
}

void ShortCircuit::on_tableView_clicked(const QModelIndex &index)
{
    Q_UNUSED(index);

    if(enlargeNum > 0)
    {
        Enlarge->Enlarge();
    }
}
