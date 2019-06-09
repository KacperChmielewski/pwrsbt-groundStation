#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "datamanager.h"

#include "QtMqtt/QMqttClient"
#include "QtMqtt/QMqttTopicFilter"

#include "logger.h"
#include "datamanager.h"

#include <iostream>
#include <math.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    log = new logger(this);
    log->setUI(ui->wLoggerBox, ui->wLoggerButton);

    dataManager* dm = new dataManager(this);
    dm->setLogger(log);
    dm->setUI(ui->hostLine, ui->portLine, ui->mqConnect);

    connect(dm, SIGNAL (pushData(QString, QString)), this, SLOT (rxData(QString, QString)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::rxData(QString head, QString value) {
    if(head == "sb/speed/pitot") {
        double v = value.toDouble();
        ui->lcdSpeed1->display(round(v*10)/10);
    } else if(head == "sb/speed/gps") {
        double v = value.toDouble();
        ui->lcdSpeed2->display(round(v*10)/10);
    } else {
        log->print(head+": "+value);
    }
}
