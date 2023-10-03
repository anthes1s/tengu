#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    QString generate_random_name();

    QStringList InputFilesToStringList(QString str);

    void WinProcessExec();

    void on_openInputFileDialog_clicked();

    void on_openInputFolderDialog_clicked();

    void on_buttonConvert_clicked();

    void on_checkBox_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
