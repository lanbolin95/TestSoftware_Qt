/********************************************************************************
** Form generated from reading UI file 'shortcircuit.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHORTCIRCUIT_H
#define UI_SHORTCIRCUIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShortCircuit
{
public:
    QGridLayout *gridLayout;
    QPushButton *CalibrationData;
    QPushButton *OpenTest;
    QPushButton *StartTest;
    QPushButton *OutData;
    QPushButton *ShortTest;
    QPushButton *FlatnessTest;
    QPushButton *InData;
    QProgressBar *progressBar;
    QPlainTextEdit *plainTextEdit;
    QTableView *tableView;
    QPlainTextEdit *plainTextEdit_2;

    void setupUi(QWidget *ShortCircuit)
    {
        if (ShortCircuit->objectName().isEmpty())
            ShortCircuit->setObjectName(QStringLiteral("ShortCircuit"));
        ShortCircuit->resize(827, 413);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ShortCircuit->sizePolicy().hasHeightForWidth());
        ShortCircuit->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(ShortCircuit);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        CalibrationData = new QPushButton(ShortCircuit);
        CalibrationData->setObjectName(QStringLiteral("CalibrationData"));

        gridLayout->addWidget(CalibrationData, 1, 0, 1, 1);

        OpenTest = new QPushButton(ShortCircuit);
        OpenTest->setObjectName(QStringLiteral("OpenTest"));

        gridLayout->addWidget(OpenTest, 3, 0, 1, 1);

        StartTest = new QPushButton(ShortCircuit);
        StartTest->setObjectName(QStringLiteral("StartTest"));

        gridLayout->addWidget(StartTest, 0, 0, 1, 1);

        OutData = new QPushButton(ShortCircuit);
        OutData->setObjectName(QStringLiteral("OutData"));

        gridLayout->addWidget(OutData, 5, 0, 1, 1);

        ShortTest = new QPushButton(ShortCircuit);
        ShortTest->setObjectName(QStringLiteral("ShortTest"));

        gridLayout->addWidget(ShortTest, 2, 0, 1, 1);

        FlatnessTest = new QPushButton(ShortCircuit);
        FlatnessTest->setObjectName(QStringLiteral("FlatnessTest"));

        gridLayout->addWidget(FlatnessTest, 4, 0, 1, 1);

        InData = new QPushButton(ShortCircuit);
        InData->setObjectName(QStringLiteral("InData"));

        gridLayout->addWidget(InData, 6, 0, 1, 1);

        progressBar = new QProgressBar(ShortCircuit);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(1);
        progressBar->setAlignment(Qt::AlignCenter);
        progressBar->setInvertedAppearance(false);
        progressBar->setTextDirection(QProgressBar::TopToBottom);

        gridLayout->addWidget(progressBar, 9, 1, 1, 1);

        plainTextEdit = new QPlainTextEdit(ShortCircuit);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(plainTextEdit->sizePolicy().hasHeightForWidth());
        plainTextEdit->setSizePolicy(sizePolicy1);
        plainTextEdit->setTabStopWidth(80);
        plainTextEdit->setCursorWidth(1);

        gridLayout->addWidget(plainTextEdit, 7, 0, 1, 1);

        tableView = new QTableView(ShortCircuit);
        tableView->setObjectName(QStringLiteral("tableView"));

        gridLayout->addWidget(tableView, 0, 1, 9, 1);

        plainTextEdit_2 = new QPlainTextEdit(ShortCircuit);
        plainTextEdit_2->setObjectName(QStringLiteral("plainTextEdit_2"));
        sizePolicy1.setHeightForWidth(plainTextEdit_2->sizePolicy().hasHeightForWidth());
        plainTextEdit_2->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(plainTextEdit_2, 8, 0, 1, 1);


        retranslateUi(ShortCircuit);

        QMetaObject::connectSlotsByName(ShortCircuit);
    } // setupUi

    void retranslateUi(QWidget *ShortCircuit)
    {
        ShortCircuit->setWindowTitle(QApplication::translate("ShortCircuit", "\346\225\260\346\215\256\346\265\213\350\257\225", Q_NULLPTR));
        CalibrationData->setText(QApplication::translate("ShortCircuit", "\346\240\241\351\252\214\346\225\260\346\215\256", Q_NULLPTR));
        OpenTest->setText(QApplication::translate("ShortCircuit", "\345\274\200\350\267\257\346\225\260\346\215\256", Q_NULLPTR));
        StartTest->setText(QApplication::translate("ShortCircuit", "\345\274\200\345\247\213\346\265\213\350\257\225", Q_NULLPTR));
        OutData->setText(QApplication::translate("ShortCircuit", "\345\257\274\345\207\272\346\225\260\346\215\256", Q_NULLPTR));
        ShortTest->setText(QApplication::translate("ShortCircuit", "\347\237\255\350\267\257\346\225\260\346\215\256", Q_NULLPTR));
        FlatnessTest->setText(QApplication::translate("ShortCircuit", "\345\271\263\346\225\264\345\272\246\346\225\260\346\215\256", Q_NULLPTR));
        InData->setText(QApplication::translate("ShortCircuit", "\345\257\274\345\205\245\346\225\260\346\215\256", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ShortCircuit: public Ui_ShortCircuit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHORTCIRCUIT_H
