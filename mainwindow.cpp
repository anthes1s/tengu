#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QToolButton>
#include <QDir>
#include <QProcess>
#include <QtGlobal>
#include <QThread>
#include <QObject>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->formatList->addItems(QStringList{".mp4", ".webm"});
    this->setFixedSize(460, 460);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openInputFileDialog_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "...", QDir::homePath());
    ui->pathToInputFile->setText(fileName);
}


void MainWindow::on_openInputFolderDialog_clicked()
{
    QString folderPath = QFileDialog::getExistingDirectory(this, "", QDir::homePath());
    ui->pathToOutputFolder->setText(folderPath);
}

void MainWindow::WinProcessExec() {
    ui->label->setText("Rendering...");
    //extract the arguments from textedit (is it a dumb way of doing so?)
    QString inputPath = ui->pathToInputFile->toPlainText();
    QString outputPath = ui->pathToOutputFolder->toPlainText();
    QString outputFileName = ui->fileName->toPlainText();
    QString outputFileFormat = ui->formatList->currentText();
    //we now form a request
    QString program{"ffmpeg"};
    QStringList arguments;
    arguments << "-i" << inputPath + ' ' << outputPath + '/' + outputFileName + outputFileFormat;
    //and execute the sysreques asynchronycally to not freeze the UI
    QFuture<void> future = QtConcurrent::run ([=]() {
    QProcess process;
    process.start(program, arguments);
    if(process.waitForFinished(-1)) ui->label->setText("SUCCESS!"); //making sure it won't kill the process too early (thx chatgpt <3)
    else ui->label->setText("FAILED :(");
    });
}

void MainWindow::on_buttonConvert_clicked()
{
    #ifdef __linux__
    ui->label->setText("i couldn't figure out how to makes this work on linux :(");
    #endif

    #ifdef _WIN32    
    WinProcessExec();
    #elif _WIN64
    WinProcessExec();
    #endif

}


