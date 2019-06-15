#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "datamanager.h"

#include "QtMqtt/QMqttClient"
#include "QtMqtt/QMqttTopicFilter"

#include "logger.h"
#include "datamanager.h"

#include "chart.h"
#include <QtCharts/QChartView>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

using namespace QtCharts;

static Chart *chart;


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

    chart = new Chart;
    chart->setTitle("Dynamic spline chart");
    chart->legend()->hide();
    chart->setAnimationOptions(QChart::AllAnimations);

    QChartView *chartView = new QChartView(chart);

    chartView->setRenderHint(QPainter::Antialiasing);


    ui->gridLayout->addWidget(chartView, 1, 1, 1, 1); // TODO move this
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::rxData(QString head, QString value) {
    if(head == "sb/speed/pitot") {
        double v = value.toDouble();
        char buff[20];
        chart->rxData(value.toDouble());
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
        sprintf(buff, "%.2f °C", v);
        ui->qBattTemp->setText(QString(buff));
    } else if(head == "sb/euler/roll") {
        double v = value.toDouble();
        char buff[20];
        sprintf(buff, "%.2f °", v);
        ui->qRoll->setText(QString(buff));
    } else if(head == "sb/euler/pitch") {
        double v = value.toDouble();
        char buff[20];
        sprintf(buff, "%.2f °", v);
        ui->qPitch->setText(QString(buff));
    } else if(head == "sb/battery/curr") {
        double v = value.toDouble();
        char buff[20];
        sprintf(buff, "%.2f A", v);
        ui->qBattCurr->setText(QString(buff));
    } else if(head == "sb/height/front") {
        double v = value.toDouble();
        char buff[20];
        sprintf(buff, "%.1f", v);
        ui->qTextHeightFront->setText(QString(buff));
        ui->qBarHeightFront->setValue(v);
    } else if(head == "sb/height/back") {
        double v = value.toDouble();
        char buff[20];
        sprintf(buff, "%.1f", v);
        ui->qTextHeightBack->setText(QString(buff));
        ui->qBarHeightBack->setValue(v);
    } else {
        log->print(head+": "+value);
    }
}
