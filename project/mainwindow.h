#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFormLayout>
#include <QLabel>
#include <QMessageBox>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>

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
    bool error_handle(QStringList);
    QStringList inputs_to_stringlist(QString);
    QString generate_random_name();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
