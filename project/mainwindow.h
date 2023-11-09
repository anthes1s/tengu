#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFormLayout>
#include <QLabel>
#include <QMessageBox>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>
#include "render-file-status.h"
#include <QIcon>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_OD_inputFiles_clicked();
    void on_OD_outputFolder_clicked();
    void on_PB_beginConvert_clicked();
    void on_GEN_randomName_clicked();
    bool error_handle();
    QString generate_random_name();
    void setInputs(QStringList);
private:
    Ui::MainWindow *ui;
    QStringList inputs;
    RenderStatus* render_status{nullptr};
    QString outputFileName;
    QString pathToOutputFolder;
    QString outputFileFormat;
};
#endif // MAINWINDOW_H
