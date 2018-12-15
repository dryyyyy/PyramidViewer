/********************************************************************************
** Form generated from reading UI file 'pyramidviewer.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PYRAMIDVIEWER_H
#define UI_PYRAMIDVIEWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PyramidViewerClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PyramidViewerClass)
    {
        if (PyramidViewerClass->objectName().isEmpty())
            PyramidViewerClass->setObjectName(QStringLiteral("PyramidViewerClass"));
        PyramidViewerClass->resize(600, 400);
        menuBar = new QMenuBar(PyramidViewerClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        PyramidViewerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(PyramidViewerClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        PyramidViewerClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(PyramidViewerClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        PyramidViewerClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(PyramidViewerClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        PyramidViewerClass->setStatusBar(statusBar);

        retranslateUi(PyramidViewerClass);

        QMetaObject::connectSlotsByName(PyramidViewerClass);
    } // setupUi

    void retranslateUi(QMainWindow *PyramidViewerClass)
    {
        PyramidViewerClass->setWindowTitle(QApplication::translate("PyramidViewerClass", "PyramidViewer", 0));
    } // retranslateUi

};

namespace Ui {
    class PyramidViewerClass: public Ui_PyramidViewerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PYRAMIDVIEWER_H
