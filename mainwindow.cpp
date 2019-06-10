#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "datamanager.h"

#include "QtMqtt/QMqttClient"
#include "QtMqtt/QMqttTopicFilter"

#include "logger.h"
#include "datamanager.h"

#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>

using namespace QtCharts;

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

    QLineSeries *series = new QLineSeries();
    series->append(0, 6);
    series->append(2, 4);
    series->append(3, 8);
    series->append(7, 4);
    series->append(10, 5);

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Speed");
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->gridLayout->addWidget(chartView, 1, 1, 1, 1); // TODO move this

    *series << QPointF(20, 2);


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
