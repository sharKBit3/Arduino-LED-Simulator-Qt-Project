/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QWidget *widget_Top;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnBuild;
    QPushButton *btnRun;
    QWidget *widget_Middle;
    QHBoxLayout *horizontalLayout_3;
    QPlainTextEdit *txtEditor;
    QGraphicsView *graphicsView;
    QWidget *widget_Bottom;
    QHBoxLayout *horizontalLayout;
    QTextEdit *txtDebug;
    QTextEdit *txtOutput;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(775, 632);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        widget_Top = new QWidget(centralwidget);
        widget_Top->setObjectName("widget_Top");
        horizontalLayout_2 = new QHBoxLayout(widget_Top);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        btnBuild = new QPushButton(widget_Top);
        btnBuild->setObjectName("btnBuild");

        horizontalLayout_2->addWidget(btnBuild);

        btnRun = new QPushButton(widget_Top);
        btnRun->setObjectName("btnRun");
        btnRun->setEnabled(false);

        horizontalLayout_2->addWidget(btnRun);


        verticalLayout->addWidget(widget_Top);

        widget_Middle = new QWidget(centralwidget);
        widget_Middle->setObjectName("widget_Middle");
        horizontalLayout_3 = new QHBoxLayout(widget_Middle);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        txtEditor = new QPlainTextEdit(widget_Middle);
        txtEditor->setObjectName("txtEditor");

        horizontalLayout_3->addWidget(txtEditor);

        graphicsView = new QGraphicsView(widget_Middle);
        graphicsView->setObjectName("graphicsView");

        horizontalLayout_3->addWidget(graphicsView);


        verticalLayout->addWidget(widget_Middle);

        widget_Bottom = new QWidget(centralwidget);
        widget_Bottom->setObjectName("widget_Bottom");
        horizontalLayout = new QHBoxLayout(widget_Bottom);
        horizontalLayout->setObjectName("horizontalLayout");
        txtDebug = new QTextEdit(widget_Bottom);
        txtDebug->setObjectName("txtDebug");

        horizontalLayout->addWidget(txtDebug);

        txtOutput = new QTextEdit(widget_Bottom);
        txtOutput->setObjectName("txtOutput");

        horizontalLayout->addWidget(txtOutput);


        verticalLayout->addWidget(widget_Bottom);


        verticalLayout_2->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 775, 22));
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
        btnBuild->setText(QCoreApplication::translate("MainWindow", "Build", nullptr));
        btnRun->setText(QCoreApplication::translate("MainWindow", "Run", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
