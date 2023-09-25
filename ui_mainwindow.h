/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTextEdit *pathToInputFile;
    QToolButton *openInputFileDialog;
    QTextEdit *pathToOutputFolder;
    QToolButton *openInputFolderDialog;
    QTextEdit *fileName;
    QPushButton *buttonConvert;
    QLabel *label;
    QComboBox *formatList;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->setEnabled(true);
        MainWindow->resize(460, 460);
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        QIcon icon;
        QString iconThemeName = QString::fromUtf8("application-x-executable");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        MainWindow->setWindowIcon(icon);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        pathToInputFile = new QTextEdit(centralwidget);
        pathToInputFile->setObjectName("pathToInputFile");
        pathToInputFile->setGeometry(QRect(10, 30, 413, 26));
        openInputFileDialog = new QToolButton(centralwidget);
        openInputFileDialog->setObjectName("openInputFileDialog");
        openInputFileDialog->setGeometry(QRect(430, 30, 26, 26));
        pathToOutputFolder = new QTextEdit(centralwidget);
        pathToOutputFolder->setObjectName("pathToOutputFolder");
        pathToOutputFolder->setGeometry(QRect(10, 80, 413, 26));
        openInputFolderDialog = new QToolButton(centralwidget);
        openInputFolderDialog->setObjectName("openInputFolderDialog");
        openInputFolderDialog->setGeometry(QRect(430, 80, 26, 26));
        fileName = new QTextEdit(centralwidget);
        fileName->setObjectName("fileName");
        fileName->setGeometry(QRect(10, 130, 363, 26));
        buttonConvert = new QPushButton(centralwidget);
        buttonConvert->setObjectName("buttonConvert");
        buttonConvert->setGeometry(QRect(10, 160, 80, 24));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 410, 441, 20));
        formatList = new QComboBox(centralwidget);
        formatList->setObjectName("formatList");
        formatList->setGeometry(QRect(380, 130, 72, 26));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 110, 361, 16));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 60, 441, 16));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(380, 110, 71, 16));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 10, 49, 16));
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
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "simple-converter", nullptr));
        openInputFileDialog->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        openInputFolderDialog->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        buttonConvert->setText(QCoreApplication::translate("MainWindow", "Convert", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        formatList->setCurrentText(QString());
        label_2->setText(QCoreApplication::translate("MainWindow", "Output File Name", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Output Folder", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Format", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Input File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
