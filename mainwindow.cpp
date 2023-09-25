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
    QString fileName = QFileDialog::getOpenFileName(this, "Choose a file...", QDir::homePath());
    ui->pathToInputFile->setText(fileName);
}


void MainWindow::on_openInputFolderDialog_clicked()
{
    QString folderPath = QFileDialog::getExistingDirectory(this, "Choose a folder for output file...", QDir::homePath());
    ui->pathToOutputFolder->setText(folderPath);
}

void MainWindow::WinProcessExec() {
    ui->label->setText("Rendering...");
    //i need to error handle wrong inputs below

    //...error handling...

    //and execute the sysreques asynchronycally to not freeze the UI
    QFuture<void> future = QtConcurrent::run ([=](){
    QProcess process;
        process.start(QString{"ffmpeg"}, QStringList() << "-i"
                                                       << ui->pathToInputFile->toPlainText() + ' '
                                                       << ui->pathToOutputFolder->toPlainText() + '/' + ui->fileName->toPlainText() + ui->formatList->currentText());

    process.waitForFinished(-1) ? ui->label->setText("SUCCESS") : ui->label->setText("FAILED :("); //waiting for a process to finish
                                                                                                   //you should never return false from it unless its a
                                                                                                   //wrong input

    });
}

void MainWindow::on_buttonConvert_clicked()
{
    #ifdef __linux__
    ui->label->setText("i couldn't figure out how to make this work on linux :(");
    #endif

    #ifdef _WIN32    
    WinProcessExec();
    #elif _WIN64
    WinProcessExec();
    #endif
}


