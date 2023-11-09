#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "render-file-status.h"

// changing the layout is for some reason unavaliable on .ui so that's the only option (probably not and i'm just retarded)
static QFormLayout* scroll_area_from_layout{nullptr};

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
    delete render_status;
    delete ui;
}

void MainWindow::setInputs(QStringList str_list){
    inputs = str_list;
}

void MainWindow::on_OD_inputFiles_clicked()
{
    QFileDialog dialog(this);
    QStringList file_names = dialog.getOpenFileNames(this, "Choose a file...", QDir::homePath(), "Videos (*.mp4 *.webm *.mkv *.avi *.mov *.gif)");
    setInputs(file_names);
    QString files{};
    for(int i{0}; i < file_names.size(); ++i) {
        files += file_names[i] + ' ';
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

    outputFileName = ui->TE_outputFileName->toPlainText();
    qDebug() << outputFileName;
    pathToOutputFolder = ui->TE_outputFolder->toPlainText();
    outputFileFormat = ui->CB_outputFileFormat->currentText();

    if(!error_handle()) return;

    bool checkbox_state { ui->GEN_randomName->checkState() ? true : false};

    if(render_status) delete render_status;
    render_status = new RenderStatus(inputs);

    QFuture<void> future = QtConcurrent::run ([=](){


        for(int i{0}; i < inputs.size(); ++i) {
            scroll_area_from_layout->addRow(render_status->getName(i), render_status->getStatus(i));
        }

        QProcess process;
        for(int i{0}; i < inputs.size(); ++i) {
            QString fileName{""};
            if(!checkbox_state) fileName = outputFileName + '_' + QString::number(i);
            else fileName = generate_random_name();                   

            process.start(QString{"ffmpeg"}, QStringList() << "-i"<< inputs[i] + ' ' << pathToOutputFolder + '/' + fileName + outputFileFormat);

            if(process.waitForFinished(-1)) {
                render_status->getName(i)->setText(fileName);
                render_status->getStatus(i)->setText("SUCCESS");
            } else {
                render_status->getName(i)->setText(fileName);
                render_status->getStatus(i)->setText("FAILED");
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
        ui->TE_outputFileName->setText("Random name will be generated");
    } else {
        ui->TE_outputFileName->setReadOnly(false);
        ui->TE_outputFileName->setText("");
    }
}

bool MainWindow::error_handle() {
    if(ui->TE_inputFiles->toPlainText().isEmpty()) {
        QMessageBox::critical(this, "Error Occurred", "\nPlease make sure that input file names are not empty\n");
        return false;
    }
    if(ui->TE_outputFolder->toPlainText().isEmpty()) {
        QMessageBox::critical(this, "Error Occurred", "\nPlease make sure that folder name is not empty\n");
        return false;
    }
    if(ui->TE_outputFileName->toPlainText().isEmpty()) {
        QMessageBox::critical(this, "Error Occurred", "\nPlease make sure that file name is not empty\n");
        return false;
    }

    for(int i{0}; i < inputs.size(); ++i) {
        QFile file {inputs[i]};
        QFileInfo info{file};
        QFile full_output{QDir::cleanPath(pathToOutputFolder + QDir::separator() + outputFileName + outputFileFormat)};
        if(full_output.exists()) {
            QMessageBox::critical(this, "Error Occurred", full_output.fileName() + "\nFile with the given name already exists\n");
            return false;
        }
        //check file format
        if(("." + info.suffix()) == ui->CB_outputFileFormat->currentText()) {
            QMessageBox::critical(this, "Error Occurred", "Cant convert " + file.fileName() + "\nInput and Output files have the same format\n");
            return false;
        }
    }
    return true;
}

QString MainWindow::generate_random_name()
{
    const int MAX_NAME_SIZE{16};    
    QString dictionary {"1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM"};
    QString name{};
    srand(time(NULL));
    for(int i{0}; i < MAX_NAME_SIZE; ++i) {
        name.push_back(dictionary[0 + rand() % (dictionary.size() - 1)]);
    }

    return name;
}

