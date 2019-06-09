#include "datamanager.h"

dataManager::dataManager(QObject *parent) : QObject(parent)
{
    this->mClient = new QMqttClient(this);


//    connect(this->mClient, SIGNAL(&QMqttClient::stateChanged), this, SLOT( mqttStatusChanged() ) );


}

void dataManager::setLogger(logger* l) {
    this->log = l;
    this->log->print("dataManager Init");
}

void dataManager::setUI(QLineEdit* host, QLineEdit* port, QPushButton* button) {
    this->qHost = host;
    this->qPort = port;
    this->qConnect = button;

    this->qHost->setText(QString("assistantintegration.dev.blebox.eu"));
    this->qPort->setText(QString("1883"));

    connect(this->qConnect, SIGNAL (released()), this, SLOT (connectButtonClicked()));


}

void dataManager::mqttStatusReport() {
    QString(QLatin1String("State Change ")
    + QString::number(this->mClient->state()));
}

void dataManager::connectButtonClicked() {
    this->mqttConnect();
}

void dataManager::mqttStatusChanged() {
    mqttStatusReport();
}


void dataManager::mqttConnect() {
    this->mClient->setHostname(this->qHost->text());
    this->mClient->setPort((qint16) this->qPort->text().toInt()); // TODO: implicit cast

    this->mClient->connectToHost();
    this->log->print("connecting to: "+ this->mClient->hostname() + ":"
                     + QString::number(this->mClient->port()) );
}
