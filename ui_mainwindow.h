/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include "Curves/curve.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    Curve *centralwidget;
    QPushButton *quadCurveButton;
    QPushButton *cubCurveButton;
    QPushButton *compCurveButton;
    QLineEdit *lineEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(802, 599);
        centralwidget = new Curve(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        quadCurveButton = new QPushButton(centralwidget);
        quadCurveButton->setObjectName(QString::fromUtf8("quadCurveButton"));
        quadCurveButton->setGeometry(QRect(0, 0, 80, 21));
        cubCurveButton = new QPushButton(centralwidget);
        cubCurveButton->setObjectName(QString::fromUtf8("cubCurveButton"));
        cubCurveButton->setGeometry(QRect(90, 0, 80, 21));
        compCurveButton = new QPushButton(centralwidget);
        compCurveButton->setObjectName(QString::fromUtf8("compCurveButton"));
        compCurveButton->setGeometry(QRect(180, 0, 80, 21));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(280, 0, 113, 21));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 802, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        quadCurveButton->setText(QCoreApplication::translate("MainWindow", "Quad. Curve", nullptr));
        cubCurveButton->setText(QCoreApplication::translate("MainWindow", "Cubic Curve", nullptr));
        compCurveButton->setText(QCoreApplication::translate("MainWindow", "Comp. Curve", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
