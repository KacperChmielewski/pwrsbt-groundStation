#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "datamanager.h"

#include "QtMqtt/QMqttClient"
#include "QtMqtt/QMqttTopicFilter"

#include "logger.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    logger* log = new logger(ui->wLoggerBox, ui->wLoggerButton);
    log->print(QString("eluwaaa"));
    log->print(QString("eluwaaa"));
    log->print(QString("eluwaaa"));
    log->print(QString("eluwaaa"));
    log->print(QString("eluwaaa"));
    log->print(QString("eluwaaa"));
    log->print(QString("eluwaaa"));
    log->print(QString("eluwaaa"));
    log->print(QString("eluwaaa"));

    log->print("siemka");
    log->print("siemka");
    log->print("siemka");
    log->print("siemka");
    log->print("siemka");
    log->print("siemka");
    log->print("siemka");
    log->print("siemka");


    ui->hostLine->setText(QString("assistantintegration.dev.blebox.eu"));
    ui->portLine->setText(QString("1883"));

    QMqttClient* mClient;
    mClient = new QMqttClient(this);
    mClient->setHostname(ui->hostLine->text());
    mClient->setPort((qint16) ui->hostLine->text().toInt()); // TODO: implicit cast


////    auto subscription = m_client->subscribe(QMqttTopicFilter(QLatin1String("sb/speed/pitot")));
////    if (!subscription) {
////        std::cout << "Could not subscribe. Is there a valid connection?" << std::endl;
//////        return;
////    }

//    std::cout << subscription->state() << std::endl;
////    auto subWindow = new SubscriptionWindow(subscription);
////    subWindow->setWindowTitle(subscription->topic().filter());
////    subWindow->show();

////    dataManager dane;
}

MainWindow::~MainWindow()
{
    delete ui;
}
