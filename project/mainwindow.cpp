#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "render-file-status.h"

static QFormLayout* scroll_area_from_layout{nullptr};
static RenderStatus* render_status_obj{nullptr};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->scrollAreaWidgetContents->setLayout(scroll_area_from_layout = new QFormLayout());
}

MainWindow::~MainWindow()
{
    delete scroll_area_from_layout;
    delete render_status_obj;
    delete ui;
}


void MainWindow::on_OD_inputFiles_clicked()
{
    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);
    QStringList fileName = dialog.getOpenFileNames(this, "Choose a file...", QDir::homePath());
    QString files{};
    for(int i{0}; i < fileName.size(); ++i) {
        files += fileName[i] + ' ';
    }
    ui->TE_inputFiles->setText(files);
}


void MainWindow::on_OD_outputFolder_clicked()
{
    ui->TE_outputFolder->setText(QFileDialog::getExistingDirectory(this, "Choose a folder for output file...", QDir::homePath()));
}


void MainWindow::on_PB_beginConvert_clicked()
{
    /*
    //linux macro
    #ifdef __linux__
    #endif
    //windows macro
    #ifdef _WIN32  
    #elif _WIN64
    #endif
    */

    QStringList inputs {inputs_to_stringlist(ui->TE_inputFiles->toPlainText())};

    if(!error_handle(inputs)) return;

    bool checkbox_state { ui->GEN_randomName->checkState() ? true : false};

    if(render_status_obj) delete render_status_obj;
    render_status_obj = new RenderStatus(inputs);

    QFuture<void> future = QtConcurrent::run ([=](){
        QString outputFileName{ui->TE_outputFileName->toPlainText()};
        QString pathToOutputFolder{ui->TE_outputFolder->toPlainText()};

        for(int i{0}; i < inputs.size(); ++i) {
            scroll_area_from_layout->addRow(render_status_obj->getName(i), render_status_obj->getStatus(i));
        }

        QProcess process;
        for(int i{0}; i < inputs.size(); ++i) {
            QString fileName{};
            if(!checkbox_state) fileName = outputFileName + '_' + QString::number(i);
            else fileName = generate_random_name();
            process.start(QString{"ffmpeg"}, QStringList() << "-i"<< inputs[i] + ' ' << pathToOutputFolder + '/' + fileName + ui->CB_outputFileFormat->currentText());

            if(process.waitForFinished(-1)) {
                render_status_obj->getName(i)->setText(fileName);
                render_status_obj->getStatus(i)->setText("SUCCESS");
            } else {
                render_status_obj->getName(i)->setText(fileName);
                render_status_obj->getStatus(i)->setText("FAILED");
            }
        }        
    });
    return;
}



void MainWindow::on_GEN_randomName_clicked()
{
    //make outputfilename non-editable and generate a random file name
    if(ui->GEN_randomName->checkState()) {
        ui->TE_outputFileName->setReadOnly(true);
        ui->TE_outputFileName->clear();
        ui->TE_outputFileName->setText("Random Name Will Be Generated");
    } else {
        ui->TE_outputFileName->setReadOnly(false);
        ui->TE_outputFileName->setText("");
    }
}

bool MainWindow::error_handle(QStringList inputs) {
    if(ui->TE_inputFiles->toPlainText() == "") {
        QMessageBox::critical(this, "Error Occurred", "Please make sure that file name is not empty");
        return false;
    }
    for(int i{0}; i < inputs.size(); ++i) {
        QFile file {inputs[i]};
        QFileInfo info{file};
        if(!file.exists()) {
            QMessageBox::critical(this, "Error Occurred", file.fileName() + " file doesn't exist, make sure file names don't contain spaces"); // fix to_stringlist()
            return false;
        }
        //check file format
        if(("." + info.suffix()) == ui->CB_outputFileFormat->currentText()) {
            QMessageBox::critical(this, "Error Occurred", "Cant convert " + file.fileName() + "\nInput and Output files have the same format");
            return false;
        }
    }
    return true;
}

QStringList MainWindow::inputs_to_stringlist(QString str)
{
    QStringList list{};
    QString tmp = "";
    for(int i{0}; i < str.size(); ++i) {
        if(str[i] != ' ') { //this makes filename invalid if it has a spacebar
            tmp += str[i];
        } else {
            list.push_back(tmp);
            tmp = "";
        }
    }
    return list;
}

QString MainWindow::generate_random_name()
{
    const int MAX_NAME_SIZE{16};
    srand(time(NULL));
    QString dictionary {"1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM"};
    QString name{};

    for(int i{0}; i < MAX_NAME_SIZE; ++i) {
        name.push_back(dictionary[0 + rand() % (dictionary.size() - 1)]);
    }

    return name;
}

