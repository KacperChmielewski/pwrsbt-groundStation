#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "datamanager.h"

#include "QtMqtt/QMqttClient"
#include "QtMqtt/QMqttTopicFilter"

#include "logger.h"
#include "datamanager.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    logger* log = new logger(this);
    log->setUI(ui->wLoggerBox, ui->wLoggerButton);

    dataManager* dm = new dataManager(this);
    dm->setLogger(log);
    dm->setUI(ui->hostLine, ui->portLine, ui->mqConnect);

    return;

    QMqttClient* mClient;
    mClient = new QMqttClient(this);


    const QString content = QLatin1String(": State Change")
                    + QString::number(mClient->state())
                    + QLatin1Char('\n');
    log->print(content);



    connect(mClient, &QMqttClient::messageReceived, this, [this](const QByteArray &message, const QMqttTopicName &topic) {
//        extern logger* log;
        const QString content = QLatin1String(" Received Topic: ")
                    + topic.name()
                    + QLatin1String(" Message: ")
                    + message
                    + QLatin1Char('\n');
        std::cout << "content" << std::endl;
//        log->print(content);
    });



    if (mClient->state() == QMqttClient::Disconnected) {
//        ui->lineEditHost->setEnabled(false);
//        ui->spinBoxPort->setEnabled(false);
//        ui->buttonConnect->setText(tr("Disconnect"));
        mClient->connectToHost();
        log->print("Laczenie");

        auto subscription = mClient->subscribe(QMqttTopicFilter("sb/speed/pitot"));
        if (!subscription) {
            log->print("Could not subscribe. Is there a valid connection?");
            return;
        }


    } else {
//        ui->lineEditHost->setEnabled(true);
//        ui->spinBoxPort->setEnabled(true);
//        ui->buttonConnect->setText(tr("Connect"));
        mClient->disconnectFromHost();
        log->print("razlaczenie");

    }


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
