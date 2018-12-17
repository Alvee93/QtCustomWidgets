#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFileDialog>
#include<QString>
#include <QDebug>

#include <stdio.h>
#include "exif.h"
#include <fstream>
#include <iostream>

#include <string>
#include <fstream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonBrowse_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "/home",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
    ui->labelDir->setText(dir);

    QDir directory(dir);
    QStringList images = directory.entryList(QStringList() << "*.jpg" << "*.JPG",QDir::Files);

    ofstream myfile;
    myfile.open ("makemodel.csv");
        foreach(QString filename, images) {
        //do whatever you need to do
            qDebug() << filename;
            QString full_filename = dir + "/" + filename;
            QByteArray ba = full_filename.toLatin1();                //Exif Parsing Begins
            const char *temp = ba.data();

            FILE *fp = fopen(temp,"rb");// binPix;

            fseek(fp, 0, SEEK_END);
            unsigned long fsize = ftell(fp);
            rewind(fp);
            unsigned char *buf = new unsigned char[fsize];

            if (fread(buf, 1, fsize, fp) != fsize) {
                //ui->exifError->setText("Cannot read file.");
                delete[] buf;
                //return 0;
              }

            fclose(fp);

            easyexif::EXIFInfo result;
            int code = result.parseFrom(buf, fsize);
            delete[] buf;
            if (code) {
                //ui->exifError->setText("Error parsing Exif data.");
              }

            myfile << result.Make.c_str() << "," << result.Model.c_str() << endl;
            qDebug() << QString::fromStdString(result.Make.c_str())
                     << ", "
                     << QString::fromStdString(result.Model.c_str());

        }

    myfile.close();
}
