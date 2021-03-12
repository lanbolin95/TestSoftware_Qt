/********************************************************************************
** Form generated from reading UI file 'drawing.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DRAWING_H
#define UI_DRAWING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Drawing
{
public:

    void setupUi(QWidget *Drawing)
    {
        if (Drawing->objectName().isEmpty())
            Drawing->setObjectName(QStringLiteral("Drawing"));
        Drawing->resize(400, 300);

        retranslateUi(Drawing);

        QMetaObject::connectSlotsByName(Drawing);
    } // setupUi

    void retranslateUi(QWidget *Drawing)
    {
        Drawing->setWindowTitle(QApplication::translate("Drawing", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Drawing: public Ui_Drawing {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DRAWING_H
