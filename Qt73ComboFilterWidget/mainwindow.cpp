#include "mainwindow.h"
#include "ui_mainwindow.h"

QString final_query;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList cameraMakes;
    cameraMakes << "Samsung" << "Microsoft" << "Nikon" << "Nokia";
    ui->comboBox_cameraMake->addItems(cameraMakes);

    QStringList locations;
    locations << "Cox's Bazar" << "Himchori" << "Dhaka" << "Rajshahi";
    ui->comboBox_location->addItems(locations);

    QStringList weathers;
    weathers << "Sunshine" << "Haze" << "Cloudy" << "Snowy";
    ui->comboBox_weather->addItems(weathers);

    QStringList persons;
    persons << "Alvee" << "Nishita" << "Prottoy" << "Mahin";
    ui->comboBox_person->addItems(persons);

    QStringList events;
    events << "Vaccation" << "Office Work" << "Home Relax" << "Lunch Out";
    ui->comboBox_event->addItems(events);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_filterButton_clicked()
{
    QString c_make = ui->comboBox_cameraMake->currentText();
    QString location = ui->comboBox_location->currentText();
    QString weather = ui->comboBox_weather->currentText();
    QString person = ui->comboBox_person->currentText();
    QString event = ui->comboBox_event->currentText();

    final_query = c_make + " " + location + " " + weather + " " + person + " " + event ;

    ui->label->setText(final_query);
}
