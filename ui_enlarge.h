/********************************************************************************
** Form generated from reading UI file 'enlarge.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ENLARGE_H
#define UI_ENLARGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_enlarge
{
public:
    QGridLayout *gridLayout;
    QLabel *label;

    void setupUi(QDialog *enlarge)
    {
        if (enlarge->objectName().isEmpty())
            enlarge->setObjectName(QStringLiteral("enlarge"));
        enlarge->resize(400, 400);
        gridLayout = new QGridLayout(enlarge);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(enlarge);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);


        retranslateUi(enlarge);

        QMetaObject::connectSlotsByName(enlarge);
    } // setupUi

    void retranslateUi(QDialog *enlarge)
    {
        enlarge->setWindowTitle(QApplication::translate("enlarge", "\346\224\276\345\244\247", Q_NULLPTR));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class enlarge: public Ui_enlarge {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENLARGE_H
