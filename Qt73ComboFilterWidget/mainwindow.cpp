#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbmanager.h" // for managing the db functionalities

#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

//QString final_query;
static const QString path = "m_managerV04.sqlite";
DbManager db(path);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//populate the cobboBoxes
    show_comboMake();

    show_comboLocation();

    show_comboWeather();

    show_comboDaylight();

    show_comboPerson();

    show_comboEvent();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_filterButton_clicked()
{
    QString final_query = "SELECT path from images WHERE ";
    QString c_make, location, weather, daylight, person, event;
    bool filter_selected = false;

    if(ui->comboBox_cameraMake->currentText() != ""){ // ui->comboBox_cameraMake->currentIndex() !=0
        c_make = ui->comboBox_cameraMake->currentText(); // the variable contains the comBo text
        final_query = final_query + "make = (:make)" + " AND ";
        filter_selected = true;
    }
    if(ui->comboBox_location->currentText() != ""){
        location = ui->comboBox_location->currentText();
        final_query = final_query + "location = (:location)" + " AND ";
        filter_selected = true;
    }
    if(ui->comboBox_weather->currentText() != ""){
        weather = ui->comboBox_weather->currentText();
        final_query = final_query + "weather_status = (:weather)" + " AND ";
        filter_selected = true;
    }
    if(ui->comboBox_daylight->currentText() != ""){
        daylight = ui->comboBox_daylight->currentText();
        final_query = final_query + "daylight_status = (:daylight_status)" + " AND ";
        filter_selected = true;
    }
    if(ui->comboBox_person->currentText() !=""){
        person = ui->comboBox_person->currentText();
        final_query = final_query + "person = (:person)" + " AND ";
        filter_selected = true;
    }
    if(ui->comboBox_event->currentText() != ""){
        event = ui->comboBox_event->currentText();
        final_query = final_query + "event = (:event)" + " AND ";
        filter_selected = true;
    }

    if(filter_selected) {
        //qDebug() << "Entered the AND removal";
        final_query = final_query.remove((final_query.size())-5, 5);
        // final_query = SELECT path from images WHERE make = (:make) AND location = (:location)
        // AND weather_status = (:weather) AND person = (:person) AND event = (:event)

        QSqlQueryModel *modal = new QSqlQueryModel;
        QSqlQuery query;
        bool success = false;
        query.prepare(final_query);
        query.bindValue(":make", c_make);
        query.bindValue(":location", location);
        query.bindValue(":weather", weather);
        query.bindValue(":daylight_status", daylight);
        query.bindValue(":person", person);
        query.bindValue(":event", event);
        success = query.exec();

        if (query.exec())
        {
           if (query.next())
           {
                modal->setQuery(query);
                ui->listView_2->setModel(modal);   // it exists
           }
        }
        else if(!success){
            qDebug() << "Filter query failed: " << query.lastError();
        }
    }

    else{
        final_query = final_query + "1 = 1";
    }

    ui->label->setText(final_query);
}

//populating the comboBoxes

void MainWindow::show_comboMake()
{
    QSqlQueryModel *modal = new QSqlQueryModel;
    QSqlQuery query;
    bool success = false;
    query.prepare("SELECT DISTINCT make FROM images");
    success = query.exec();
    if(!success){
        qDebug() << "Fetching makes failed: " << query.lastError();
    }

    modal->setQuery(query);
    ui->comboBox_cameraMake->setModel(modal);
}

void MainWindow::show_comboLocation()
{
    QSqlQueryModel *modal = new QSqlQueryModel;
    QSqlQuery query;
    bool success = false;
    query.prepare("SELECT DISTINCT location FROM images");
    success = query.exec();
    if(!success){
        qDebug() << "Fetching locations failed: " << query.lastError();
    }

    modal->setQuery(query);
    ui->comboBox_location->setModel(modal);
}

void MainWindow::show_comboWeather()
{
    QSqlQueryModel *modal = new QSqlQueryModel;
    QSqlQuery query;
    bool success = false;
    query.prepare("SELECT DISTINCT weather_status FROM images");
    success = query.exec();
    if(!success){
        qDebug() << "Fetching weathers failed: " << query.lastError();
    }

    modal->setQuery(query);
    ui->comboBox_weather->setModel(modal);
}

void MainWindow::show_comboDaylight()
{
    QSqlQueryModel *modal = new QSqlQueryModel;
    QSqlQuery query;
    bool success = false;
    query.prepare("SELECT DISTINCT daylight_status FROM images");
    success = query.exec();
    if(!success){
        qDebug() << "Fetching daylights failed: " << query.lastError();
    }

    modal->setQuery(query);
    ui->comboBox_daylight->setModel(modal);
}

void MainWindow::show_comboPerson()
{
    QSqlQueryModel *modal = new QSqlQueryModel;
    QSqlQuery query;
    bool success = false;
    query.prepare("SELECT DISTINCT person FROM images");
    success = query.exec();
    if(!success){
        qDebug() << "Fetching persons failed: " << query.lastError();
    }

    modal->setQuery(query);
    ui->comboBox_person->setModel(modal);
}

void MainWindow::show_comboEvent()
{
    QSqlQueryModel *modal = new QSqlQueryModel;
    QSqlQuery query;
    bool success = false;
    query.prepare("SELECT DISTINCT event FROM images");
    success = query.exec();
    if(!success){
        qDebug() << "Fetching events failed: " << query.lastError();
    }

    modal->setQuery(query);
    ui->comboBox_event->setModel(modal);
}
