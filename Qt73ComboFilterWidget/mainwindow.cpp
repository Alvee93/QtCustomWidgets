#include "mainwindow.h"
#include "ui_mainwindow.h"

//QString final_query;

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
    QString final_query = "SELECT path from images WHERE ";
    QString c_make, location, weather, person, event;
    bool filter_selected = false;

    if(ui->comboBox_cameraMake->currentIndex() !=0){
        c_make = ui->comboBox_cameraMake->currentText();
        final_query = final_query + "make = " + c_make + " AND ";
        filter_selected = true;
    }
    if(ui->comboBox_location->currentIndex() !=0){
        location = ui->comboBox_location->currentText();
        final_query = final_query + "location = " + location + " AND ";
        filter_selected = true;
    }
    if(ui->comboBox_weather->currentIndex() !=0){
        weather = ui->comboBox_weather->currentText();
        final_query = final_query + "weather = " + weather + " AND ";
        filter_selected = true;
    }
    if(ui->comboBox_person->currentIndex() !=0){
        person = ui->comboBox_person->currentText();
        final_query = final_query + "person = " + person + " AND ";
        filter_selected = true;
    }
    if(ui->comboBox_event->currentIndex() !=0){
        event = ui->comboBox_event->currentText();
        final_query = final_query + "event = " + event + " AND ";
        filter_selected = true;
    }

    else if(filter_selected) {
        final_query = final_query.remove((final_query.size())-5, 5);
    }

    else{
        final_query = final_query + "1 = 1";
    }
    //final_query = "SELECT path from images WHERE make = " + c_make + " AND location = " + location + " AND weather = " + weather + " AND person = " + person + " AND event = " + event
    //        + " AND";

    ui->label->setText(final_query);
}
