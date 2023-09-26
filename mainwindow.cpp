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
    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    QStringList fileName = dialog.getOpenFileNames(this, "Choose a file...", QDir::homePath());

    QString files{};

    for(int i{0}; i < fileName.size(); ++i) {
        files += fileName[i] + ' ';
    }

    ui->pathToInputFile->setText(files);

}


void MainWindow::on_openInputFolderDialog_clicked()
{
    ui->pathToOutputFolder->setText(QFileDialog::getExistingDirectory(this, "Choose a folder for output file...", QDir::homePath()));
}

QStringList MainWindow::toStringList(QString str) {
    QStringList list{};

    qDebug() << str;

    QString tmp = "";
    for(int i{0}; i < str.size(); ++i) {
        if(str[i] != ' ') {
            tmp += str[i];
        } else {
            list.push_back(tmp);
            tmp = "";
        }
    }

    return list;
}

void MainWindow::WinProcessExec() {
    //i need to error handle wrong inputs below
    QString errorMsg{};

    if(ui->pathToInputFile->toPlainText() == "") {
        errorMsg += "Invalid Input Path ";
        ui->label->setText(errorMsg);
        return;
    }
    if(ui->pathToOutputFolder->toPlainText() == "") {
        errorMsg += "Invalid Output Path ";
        ui->label->setText(errorMsg);
        return;
    }
    if(ui->fileName->toPlainText() == "") {
        errorMsg += "Invalid File Name ";
        ui->label->setText(errorMsg);
        return;
    }

    ui->label->setText("Rendering...");
    //creating stringlist to use it for multifile render
    QString labelInputPath{ui->pathToInputFile->toPlainText()};
    QStringList inputs = toStringList(labelInputPath);

    //and execute the sysreques asynchronycally to not freeze the UI
    QFuture<void> future = QtConcurrent::run ([=](){
    QProcess process;
        for(int i{0}; i < inputs.size(); ++i) {
        //error handle the same file name
            QString fileName{ui->fileName->toPlainText() + QChar{i + 48}}; //this will make filename weird if i > 9;
                                                                           //so i need to fix this with a standart func or lambda to return proper filex index


        process.start(QString{"ffmpeg"}, QStringList() << "-i"
                                                       << inputs[i] + ' '
                                                           << ui->pathToOutputFolder->toPlainText() + '/' + fileName + ui->formatList->currentText());

        process.waitForFinished(-1) ? ui->label->setText("SUCCESS") : ui->label->setText("FAILED :("); //waiting for a process to finish
                                                                                                       //you should never return false from it unless its a
                                                                                                       //wrong input
        }
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


