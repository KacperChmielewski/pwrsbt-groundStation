#include "datamanager.h"

DataManager::DataManager(QObject *parent) : QObject(parent)
{
    mClient = new QMqttClient(this);


    connect(mClient, &QMqttClient::stateChanged, this, &DataManager::mqttStatusChanged);  // todo idk whats goin on here
    connect(mClient, &QMqttClient::messageReceived, this, &DataManager::mqttMessageRX);

}

void DataManager::setLogger(Logger* l) {
    log = l;
    log->print("dataManager Init");
}

void DataManager::setUI(QLineEdit* host, QLineEdit* port, QPushButton* button) {
    qHost = host;
    qPort = port;
    qConnect = button;

    qHost->setText(QString("assistantintegration.dev.blebox.eu"));
    qPort->setText(QString("1883"));

    connect(qConnect, SIGNAL (released()), this, SLOT (connectButtonClicked()));
}

void DataManager::mqttStatusReport() {

    QString state;

    switch (mClient->state()) {
    case QMqttClient::Disconnected:
        state = "disconnected";
        break;
    case QMqttClient::Connecting:
        state = "connecting";
        break;
    case QMqttClient::Connected:
        state = "connected";
        break;
    }
    log->print(QString(QLatin1String("MQTT: status: ") + state));
}



void DataManager::connectButtonClicked() {
    if(mClient->state() == QMqttClient::Connected) {
        mqttDisconnect();
    } else {
        mqttConnect();
    }
}

void DataManager::mqttStatusChanged() {
    mqttStatusReport();
    uiUpdate();
    mqttSubscribe();

}


void DataManager::mqttConnect() {
    mClient->setHostname(qHost->text());
    mClient->setPort((qint16) qPort->text().toInt()); // TODO: implicit cast

    mClient->connectToHost();
    log->print("connecting to: "+ mClient->hostname() + ":"
                     + QString::number(mClient->port()) );
}

void DataManager::mqttDisconnect() {
    mClient->disconnectFromHost();
}

void DataManager::mqttSubscribe() {
    if(mClient->state() == QMqttClient::Connected){
        auto subscription = mClient->subscribe(QMqttTopicFilter("#"));
        if (!subscription) {
            log->print("Could not subscribe. Is there a valid connection?");
        }
    }
}

void DataManager::mqttMessageRX(const QByteArray &message, const QMqttTopicName &topic) {
//    log->print(topic.name() + ": " + message);
    emit pushData(topic.name(), QString(message));
}

void DataManager::uiUpdate() {
    if(mClient->state() == QMqttClient::Connected) {
        qHost->setDisabled(true);
        qPort->setDisabled(true);
        qConnect->setText("Disconnect");
    } else {
        qHost->setDisabled(false);
        qPort->setDisabled(false);
        qConnect->setText("Connect");
    }
}
