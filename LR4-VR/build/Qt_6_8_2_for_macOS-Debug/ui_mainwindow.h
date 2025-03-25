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
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *circle;
    QAction *square;
    QAction *ellipse;
    QAction *action;
    QAction *triangle;
    QAction *rectangle;
    QAction *chooseColor_2;
    QAction *chooseColor;
    QWidget *centralwidget;
    QFrame *frame;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        circle = new QAction(MainWindow);
        circle->setObjectName("circle");
        square = new QAction(MainWindow);
        square->setObjectName("square");
        ellipse = new QAction(MainWindow);
        ellipse->setObjectName("ellipse");
        action = new QAction(MainWindow);
        action->setObjectName("action");
        triangle = new QAction(MainWindow);
        triangle->setObjectName("triangle");
        rectangle = new QAction(MainWindow);
        rectangle->setObjectName("rectangle");
        chooseColor_2 = new QAction(MainWindow);
        chooseColor_2->setObjectName("chooseColor_2");
        chooseColor = new QAction(MainWindow);
        chooseColor->setObjectName("chooseColor");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(170, 80, 471, 291));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 38));
        menu = new QMenu(menubar);
        menu->setObjectName("menu");
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName("menu_2");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menu->addAction(circle);
        menu->addAction(square);
        menu->addAction(ellipse);
        menu->addAction(triangle);
        menu->addAction(rectangle);
        menu->addAction(action);
        menu_2->addAction(chooseColor);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        circle->setText(QCoreApplication::translate("MainWindow", "\320\232\321\200\321\203\320\263", nullptr));
        square->setText(QCoreApplication::translate("MainWindow", "\320\232\320\262\320\260\320\264\321\200\320\260\321\202", nullptr));
        ellipse->setText(QCoreApplication::translate("MainWindow", "\320\255\320\273\320\273\320\270\320\277\321\201", nullptr));
        action->setText(QCoreApplication::translate("MainWindow", ".", nullptr));
        triangle->setText(QCoreApplication::translate("MainWindow", "\320\242\321\200\320\265\321\203\320\263\320\276\320\273\321\214\320\275\320\270\320\272", nullptr));
        rectangle->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\321\217\320\274\320\276\321\203\320\263\320\276\320\273\321\214\320\275\320\270\320\272", nullptr));
        chooseColor_2->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265 \321\206\320\262\320\265\321\202", nullptr));
        chooseColor->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265 \321\206\320\262\320\265\321\202", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\320\244\320\270\320\263\321\203\321\200\321\213", nullptr));
        menu_2->setTitle(QCoreApplication::translate("MainWindow", "\320\246\320\262\320\265\321\202", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
