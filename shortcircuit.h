#ifndef SHORTCIRCUIT_H
#define SHORTCIRCUIT_H

#include <QDialog>
#include <QStandardItemModel>
#include "usboperation.h"

namespace Ui {
class ShortCircuit;
}

class ShortCircuit : public QDialog
{
    Q_OBJECT

public:
    ShortCircuit(QWidget *parent = 0);
    ~ShortCircuit();

//    UsbOperation *usbOpera;
    void GetRowColumn();
    void MakingTables(int ColumnCount, int RowCount);
    bool saveBinaryFile(QString &aFileName);
    bool openBinaryFile(QString &aFileName);
    void resetTable(int aRowCount, int aColumnCount);

private slots:
    void on_CalibrationData_clicked();

    void on_OutData_clicked();

    void on_InData_clicked();

    void on_ShortTest_clicked();

    void on_OpenTest_clicked();

    void on_FlatnessTest_clicked();

    void on_StartTest_clicked();

    void ShortError();

    void OpenError();

    void keyPressEvent(QKeyEvent *e);

private:
    Ui::ShortCircuit *ui;

    UsbOperation *usbOpera;

    QStandardItemModel *standItemModel;
//    QStandardItemModel *theModel;
};

#endif // SHORTCIRCUIT_H
