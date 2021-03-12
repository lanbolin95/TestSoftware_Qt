/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QPlainTextEdit *plainTextEdit;
    QPushButton *ConnectDevice;
    QPushButton *DataShow;
    QPushButton *Drawing;
    QPushButton *Reset;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(400, 292);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        plainTextEdit = new QPlainTextEdit(centralWidget);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));

        gridLayout->addWidget(plainTextEdit, 2, 0, 1, 2);

        ConnectDevice = new QPushButton(centralWidget);
        ConnectDevice->setObjectName(QStringLiteral("ConnectDevice"));

        gridLayout->addWidget(ConnectDevice, 0, 0, 1, 1);

        DataShow = new QPushButton(centralWidget);
        DataShow->setObjectName(QStringLiteral("DataShow"));

        gridLayout->addWidget(DataShow, 3, 0, 1, 1);

        Drawing = new QPushButton(centralWidget);
        Drawing->setObjectName(QStringLiteral("Drawing"));

        gridLayout->addWidget(Drawing, 3, 1, 1, 1);

        Reset = new QPushButton(centralWidget);
        Reset->setObjectName(QStringLiteral("Reset"));

        gridLayout->addWidget(Reset, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 29));
        MainWindow->setMenuBar(menuBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\346\265\213\350\257\225\350\275\257\344\273\266", Q_NULLPTR));
        ConnectDevice->setText(QApplication::translate("MainWindow", "\350\277\236\346\216\245\350\256\276\345\244\207", Q_NULLPTR));
        DataShow->setText(QApplication::translate("MainWindow", "\346\225\260\346\215\256\346\265\213\350\257\225", Q_NULLPTR));
        Drawing->setText(QApplication::translate("MainWindow", "\347\224\273\345\233\276", Q_NULLPTR));
        Reset->setText(QApplication::translate("MainWindow", "\351\207\215\347\275\256\350\256\276\345\244\207", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
