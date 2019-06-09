#include "datamanager.h"

dataManager::dataManager(QObject *parent) : QObject(parent)
{
    this->mClient = new QMqttClient(this);


    connect(this->mClient, &QMqttClient::stateChanged, this, &dataManager::mqttStatusChanged);  // todo idk whats goin on here


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

    QString state;

    switch (this->mClient->state()) {
    case QMqttClient::ClientState::Disconnected:
        state = "disconnected";
        break;
    case QMqttClient::ClientState::Connecting:
        state = "connecting";
        break;
    case QMqttClient::ClientState::Connected:
        state = "connected";
        break;
    }
    this->log->print(QString(QLatin1String("MQTT: status: ") + state));

    // todo kontrolki

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
