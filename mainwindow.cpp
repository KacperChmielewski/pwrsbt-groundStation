#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "datamanager.h"

#include "QtMqtt/QMqttClient"
#include "QtMqtt/QMqttTopicFilter"

#include "logger.h"
#include "datamanager.h"

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
        char buff[20];
        sprintf(buff, "%.1f", v);
        ui->lcdSpeed1->display(QString(buff));
    } else if(head == "sb/speed/gps") {
        double v = value.toDouble();
        char buff[20];
        sprintf(buff, "%.1f", v);
        ui->lcdSpeed2->display(QString(buff));
    } else if(head == "sb/battery/voltage") {
        double v = value.toDouble();
        char buff[20];
        sprintf(buff, "%.2f V", v);
        ui->qBattU->setText(QString(buff));
    } else if(head == "sb/battery/temp") {
        double v = value.toDouble();
        char buff[20];
        sprintf(buff, "%.2f *C", v);
        ui->qBattTemp->setText(QString(buff));
    } else {
        log->print(head+": "+value);
    }
}
