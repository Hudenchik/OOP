/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLineEdit *lineEditA;
    QLineEdit *lineEditB;
    QLineEdit *lineEditC;
    QSpinBox *spinBoxA;
    QSpinBox *spinBoxB;
    QSpinBox *spinBoxC;
    QSlider *sliderA;
    QSlider *sliderB;
    QSlider *sliderC;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(603, 384);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(70, 60, 451, 61));
        QFont font;
        font.setPointSize(70);
        label->setFont(font);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label->setMargin(0);
        lineEditA = new QLineEdit(centralwidget);
        lineEditA->setObjectName("lineEditA");
        lineEditA->setGeometry(QRect(80, 140, 113, 21));
        lineEditB = new QLineEdit(centralwidget);
        lineEditB->setObjectName("lineEditB");
        lineEditB->setGeometry(QRect(230, 140, 113, 21));
        lineEditC = new QLineEdit(centralwidget);
        lineEditC->setObjectName("lineEditC");
        lineEditC->setGeometry(QRect(390, 140, 113, 21));
        spinBoxA = new QSpinBox(centralwidget);
        spinBoxA->setObjectName("spinBoxA");
        spinBoxA->setGeometry(QRect(80, 170, 111, 22));
        spinBoxB = new QSpinBox(centralwidget);
        spinBoxB->setObjectName("spinBoxB");
        spinBoxB->setGeometry(QRect(230, 170, 111, 22));
        spinBoxC = new QSpinBox(centralwidget);
        spinBoxC->setObjectName("spinBoxC");
        spinBoxC->setGeometry(QRect(390, 170, 111, 22));
        sliderA = new QSlider(centralwidget);
        sliderA->setObjectName("sliderA");
        sliderA->setGeometry(QRect(80, 210, 111, 25));
        sliderA->setOrientation(Qt::Orientation::Horizontal);
        sliderB = new QSlider(centralwidget);
        sliderB->setObjectName("sliderB");
        sliderB->setGeometry(QRect(230, 210, 111, 25));
        sliderB->setOrientation(Qt::Orientation::Horizontal);
        sliderC = new QSlider(centralwidget);
        sliderC->setObjectName("sliderC");
        sliderC->setGeometry(QRect(390, 210, 111, 25));
        sliderC->setOrientation(Qt::Orientation::Horizontal);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 603, 38));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "A <= B <= C", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
