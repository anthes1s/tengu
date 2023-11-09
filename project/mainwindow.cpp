#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "render-file-status.h"

// changing the layout is for some reason unavaliable on .ui so that's the only option (probably not and i'm just retarded)
static QFormLayout* scroll_area_from_layout{nullptr};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);
    _ui->scrollAreaWidgetContents->setLayout(scroll_area_from_layout = new QFormLayout());

    //changing color of buttons (for some reason they ignore palette settings from the .ui)
    _ui->PB_beginConvert->setStyleSheet(QString::fromUtf8("background-color: #343434; color: #ffffff; border-color: #4e4e4e"));
    _ui->CB_outputFileFormat->setStyleSheet(QString::fromUtf8("background-color: #343434; color: #ffffff; border-color: #4e4e4e"));
    _ui->OD_inputFiles->setStyleSheet(QString::fromUtf8("background-color: #343434; color: #ffffff; border-color: #4e4e4e"));
    _ui->OD_outputFolder->setStyleSheet(QString::fromUtf8("background-color: #343434; color: #ffffff; border-color: #4e4e4e"));

}

MainWindow::~MainWindow()
{
    delete scroll_area_from_layout;
    delete _render_status;
    delete _ui;
}

void MainWindow::setInputs(QStringList& str_list){
    _inputs = str_list;
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
    _ui->TE_inputFiles->setText(files);
}


void MainWindow::on_OD_outputFolder_clicked()
{
    _ui->TE_outputFolder->setText(QFileDialog::getExistingDirectory(this, "Choose a folder for output file...", QDir::homePath()));
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

    _outputFileName = _ui->TE_outputFileName->toPlainText();
    _pathToOutputFolder = _ui->TE_outputFolder->toPlainText();
    _outputFileFormat = _ui->CB_outputFileFormat->currentText();

    if(!error_handle()) return;

    bool checkbox_state { _ui->GEN_randomName->checkState() ? true : false};

    if(_render_status) delete _render_status;
    _render_status = new RenderStatus(_inputs);

    QFuture<void> future = QtConcurrent::run ([=](){ //wrap this into a different function


        for(int i{0}; i < _inputs.size(); ++i) {
            scroll_area_from_layout->addRow(_render_status->getName(i), _render_status->getStatus(i));
        }

        QProcess process;
        for(int i{0}; i < _inputs.size(); ++i) {
            QString fileName{""};
            if(!checkbox_state) fileName = _outputFileName + '_' + QString::number(i);
            else fileName = generate_random_name();                   

            process.start(QString{"ffmpeg"}, QStringList() << "-i"<< _inputs[i] + ' ' << _pathToOutputFolder + '/' + fileName + _outputFileFormat);

            if(process.waitForFinished(-1)) {
                _render_status->getName(i)->setText(fileName);
                _render_status->getStatus(i)->setText("SUCCESS");
            } else {
                _render_status->getName(i)->setText(fileName);
                _render_status->getStatus(i)->setText("FAILED");
            }
        }        
    });
    return;
}

void MainWindow::on_GEN_randomName_clicked()
{
    //make outputfilename non-editable and generate a random file name
    if(_ui->GEN_randomName->checkState()) {
        _ui->TE_outputFileName->setReadOnly(true);
        _ui->TE_outputFileName->clear();
        _ui->TE_outputFileName->setText("Random name will be generated");
    } else {
        _ui->TE_outputFileName->setReadOnly(false);
        _ui->TE_outputFileName->setText("");
    }
}

bool MainWindow::error_handle() {
    if(_ui->TE_inputFiles->toPlainText().isEmpty()) {
        QMessageBox::critical(this, "Error Occurred", "\nPlease make sure that input file names are not empty\n");
        return false;
    }
    if(_ui->TE_outputFolder->toPlainText().isEmpty()) {
        QMessageBox::critical(this, "Error Occurred", "\nPlease make sure that folder name is not empty\n");
        return false;
    }
    if(_ui->TE_outputFileName->toPlainText().isEmpty()) {
        QMessageBox::critical(this, "Error Occurred", "\nPlease make sure that file name is not empty\n");
        return false;
    }

    for(int i{0}; i < _inputs.size(); ++i) {
        QFile file {_inputs[i]};
        QFileInfo info{file};
        QFile full_output{QDir::cleanPath(_pathToOutputFolder + QDir::separator() + _outputFileName + _outputFileFormat)};
        if(full_output.exists()) {
            QMessageBox::critical(this, "Error Occurred", full_output.fileName() + "\nFile with the given name already exists\n");
            return false;
        }
        //check file format
        if(("." + info.suffix()) == _ui->CB_outputFileFormat->currentText()) {
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

