/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTextEdit *TE_inputFiles;
    QTextEdit *TE_outputFolder;
    QTextEdit *TE_outputFileName;
    QComboBox *CB_outputFileFormat;
    QToolButton *OD_inputFiles;
    QToolButton *OD_outputFolder;
    QCheckBox *GEN_randomName;
    QPushButton *PB_beginConvert;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(460, 460);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(460, 460));
        MainWindow->setMaximumSize(QSize(460, 460));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        TE_inputFiles = new QTextEdit(centralwidget);
        TE_inputFiles->setObjectName("TE_inputFiles");
        TE_inputFiles->setGeometry(QRect(10, 10, 415, 26));
        TE_outputFolder = new QTextEdit(centralwidget);
        TE_outputFolder->setObjectName("TE_outputFolder");
        TE_outputFolder->setGeometry(QRect(10, 40, 415, 26));
        TE_outputFileName = new QTextEdit(centralwidget);
        TE_outputFileName->setObjectName("TE_outputFileName");
        TE_outputFileName->setGeometry(QRect(10, 70, 365, 26));
        CB_outputFileFormat = new QComboBox(centralwidget);
        CB_outputFileFormat->addItem(QString());
        CB_outputFileFormat->addItem(QString());
        CB_outputFileFormat->addItem(QString());
        CB_outputFileFormat->addItem(QString());
        CB_outputFileFormat->addItem(QString());
        CB_outputFileFormat->addItem(QString());
        CB_outputFileFormat->setObjectName("CB_outputFileFormat");
        CB_outputFileFormat->setGeometry(QRect(380, 70, 71, 26));
        OD_inputFiles = new QToolButton(centralwidget);
        OD_inputFiles->setObjectName("OD_inputFiles");
        OD_inputFiles->setGeometry(QRect(430, 10, 26, 26));
        OD_outputFolder = new QToolButton(centralwidget);
        OD_outputFolder->setObjectName("OD_outputFolder");
        OD_outputFolder->setGeometry(QRect(430, 40, 26, 26));
        GEN_randomName = new QCheckBox(centralwidget);
        GEN_randomName->setObjectName("GEN_randomName");
        GEN_randomName->setGeometry(QRect(10, 100, 440, 26));
        PB_beginConvert = new QPushButton(centralwidget);
        PB_beginConvert->setObjectName("PB_beginConvert");
        PB_beginConvert->setGeometry(QRect(10, 130, 440, 26));
        scrollArea = new QScrollArea(centralwidget);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setGeometry(QRect(10, 160, 440, 270));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 438, 268));
        scrollArea->setWidget(scrollAreaWidgetContents);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 460, 21));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "gui-ffmpeg-converter", nullptr));
        TE_inputFiles->setPlaceholderText(QCoreApplication::translate("MainWindow", "Path to an Input File(-s)", nullptr));
        TE_outputFolder->setPlaceholderText(QCoreApplication::translate("MainWindow", "Path to the File(-s) Output Folder", nullptr));
        TE_outputFileName->setPlaceholderText(QCoreApplication::translate("MainWindow", "Enter Output File Name", nullptr));
        CB_outputFileFormat->setItemText(0, QCoreApplication::translate("MainWindow", ".mp4", nullptr));
        CB_outputFileFormat->setItemText(1, QCoreApplication::translate("MainWindow", ".webm", nullptr));
        CB_outputFileFormat->setItemText(2, QCoreApplication::translate("MainWindow", ".mkv", nullptr));
        CB_outputFileFormat->setItemText(3, QCoreApplication::translate("MainWindow", ".avi", nullptr));
        CB_outputFileFormat->setItemText(4, QCoreApplication::translate("MainWindow", ".mov", nullptr));
        CB_outputFileFormat->setItemText(5, QCoreApplication::translate("MainWindow", ".gif", nullptr));

        OD_inputFiles->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        OD_outputFolder->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        GEN_randomName->setText(QCoreApplication::translate("MainWindow", "Generate Random Name", nullptr));
        PB_beginConvert->setText(QCoreApplication::translate("MainWindow", "Convert", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
