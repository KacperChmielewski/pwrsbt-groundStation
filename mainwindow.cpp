#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "datamanager.h"

#include "QtMqtt/QMqttClient"
#include "QtMqtt/QMqttTopicFilter"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    const QString content = QLatin1String("Testowy log\r\n");

    ui->wLoggerBox->setReadOnly(true);
    ui->wLoggerBox->insertPlainText(content);
    ui->wLoggerBox->insertPlainText(content);
    ui->wLoggerBox->insertPlainText(content);
    ui->wLoggerBox->insertPlainText(content);
    ui->wLoggerBox->insertPlainText(content);
    ui->wLoggerBox->insertPlainText(content);
    ui->wLoggerBox->insertPlainText(content);
    ui->wLoggerBox->insertPlainText(content);
    ui->wLoggerBox->insertPlainText(content);

    const QString content2 = QLatin1String("Testowy log222\r\n");
    ui->wLoggerBox->insertPlainText(content2);

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
