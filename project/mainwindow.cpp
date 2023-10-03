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

QStringList MainWindow::InputFilesToStringList(QString str)
{
    QStringList list{};
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

//this need some refactoring
void MainWindow::WinProcessExec()
{
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
    //creating stringlist to use it for multifile render
    QStringList inputs{InputFilesToStringList(ui->pathToInputFile->toPlainText())};
    //and execute the sysreques asynchronycally to not freeze the UI
    QFuture<void> future = QtConcurrent::run ([=](){
    QProcess process;
        for(int i{0}; i < inputs.size(); ++i) {
        //error handle the same file name
        //also create a conditional to use a random name checkBox
        QString fileName{};
        if(!ui->checkBox->checkState()) {
        fileName = ui->fileName->toPlainText() + '_' + QChar{i + 48};
        } else fileName = generate_random_name();
        //this will make filename weird if i > 9 (i being a file that is going to be rendered);
        //so i need to fix this with a standart func or lambda to return proper filex index
        //also i have to make checkbox disabled somehow during the execution of the process

        ui->label->setText("Rendering... " + fileName);
        process.start(QString{"ffmpeg"}, QStringList() << "-i"
                                                       << inputs[i] + ' '
                                                       << ui->pathToOutputFolder->toPlainText() + '/' + fileName + ui->formatList->currentText());
                                                       //also add a way to choose a profile and a rendering codec

        process.waitForFinished(-1) ? ui->label->setText("SUCCESS") : ui->label->setText("FAILED :("); //waiting for a process to finish
                                                                                                       //this should never return false from it unless its a
                                                                                                       //wrong input

        }
    });
}

void MainWindow::on_buttonConvert_clicked()
{
    //linux macro
    #ifdef __linux__
    ui->label->setText("i couldn't figure out how to make this work on linux :(");
    #endif

    //windows macro
    #ifdef _WIN32 
    WinProcessExec();
    #elif _WIN64
    WinProcessExec();
    #endif

    return;
}

//create random name generator;
QString MainWindow::generate_random_name()
{
    const int max_name_size{16};
    srand(time(NULL));
    QString dictionary {"1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM"};
    QString name{};

    for(int i{0}; i < max_name_size; ++i) {
        name.push_back(dictionary[0 + rand() % (dictionary.size() - 1)]);
    }

    return name;
}

void MainWindow::on_checkBox_clicked()
{
//make outputfilename non-editable and generate a random file name
    if(ui->checkBox->checkState()) {
        ui->fileName->setReadOnly(true);
        ui->fileName->clear();
        ui->fileName->setText("Random Name Will Be Generated");
    } else {
      ui->fileName->setReadOnly(false);
        ui->fileName->setText("");
    }
}

