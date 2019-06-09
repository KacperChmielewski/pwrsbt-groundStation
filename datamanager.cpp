#include "datamanager.h"

dataManager::dataManager(QObject *parent) : QObject(parent)
{
    mClient = new QMqttClient(this);


    connect(mClient, &QMqttClient::stateChanged, this, &dataManager::mqttStatusChanged);  // todo idk whats goin on here
    connect(mClient, &QMqttClient::messageReceived, this, &dataManager::mqttMessageRX);

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



void dataManager::connectButtonClicked() {
    if(mClient->state() == QMqttClient::Connected) {
        mqttDisconnect();
    } else {
        mqttConnect();
    }
}

void dataManager::mqttStatusChanged() {
    mqttStatusReport();
    uiUpdate();
    mqttSubscribe();

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

void dataManager::mqttSubscribe() {
    if(mClient->state() == QMqttClient::Connected){
        log->print("Subuj");

        auto subscription = mClient->subscribe(QMqttTopicFilter("sb/speed/pitot"));
        if (!subscription) {
            log->print("Could not subscribe. Is there a valid connection?");
        }
    }
}

void dataManager::mqttMessageRX(const QByteArray &message, const QMqttTopicName &topic) {
    log->print("ramka!");
}

void dataManager::uiUpdate() {
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
