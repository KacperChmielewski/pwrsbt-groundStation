#include "datamanager.h"

dataManager::dataManager(QObject *parent) : QObject(parent)
{
    mClient = new QMqttClient(this);


    connect(mClient, &QMqttClient::stateChanged, this, &dataManager::mqttStatusChanged);  // todo idk whats goin on here


}

void dataManager::setLogger(logger* l) {
    log = l;
    log->print("dataManager Init");
}

void dataManager::setUI(QLineEdit* host, QLineEdit* port, QPushButton* button) {
    qHost = host;
    qPort = port;
    qConnect = button;

    qHost->setText(QString("assistantintegration.dev.blebox.eu"));
    qPort->setText(QString("1883"));

    connect(qConnect, SIGNAL (released()), this, SLOT (connectButtonClicked()));
}

void dataManager::mqttStatusReport() {

    QString state;

    switch (mClient->state()) {
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
    log->print(QString(QLatin1String("MQTT: status: ") + state));

    // todo kontrolki
    uiUpdate();

}



void dataManager::connectButtonClicked() {
    if(mClient->state() == QMqttClient::ClientState::Connected) {
        mqttDisconnect();
    } else {
        mqttConnect();
    }
}

void dataManager::mqttStatusChanged() {
    mqttStatusReport();
}


void dataManager::mqttConnect() {
    mClient->setHostname(qHost->text());
    mClient->setPort((qint16) qPort->text().toInt()); // TODO: implicit cast

    mClient->connectToHost();
    log->print("connecting to: "+ mClient->hostname() + ":"
                     + QString::number(mClient->port()) );
}

void dataManager::mqttDisconnect() {
    mClient->disconnectFromHost();
}

void dataManager::uiUpdate() {
    if(mClient->state() == QMqttClient::ClientState::Connected) {
        qHost->setDisabled(true);
        qPort->setDisabled(true);
        qConnect->setText("Disconnect");
    } else {
        qHost->setDisabled(false);
        qPort->setDisabled(false);
        qConnect->setText("Connect");
    }
}
