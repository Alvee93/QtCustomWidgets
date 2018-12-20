#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <string>
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButtonBrowse_clicked();
    void writeToFile(int i, string c_make, string c_model);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
