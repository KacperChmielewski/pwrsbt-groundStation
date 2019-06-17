#ifndef DATAMANAGER_H
#define DATAMANAGER_H


#include <QObject>

#include <QMqttClient>

#include <QLineEdit>
#include <QPushButton>

#include "logger.h"

class DataManager : public QObject
{
    Q_OBJECT
private:
    QMqttClient* mClient;
    Logger* log;
    QLineEdit* qHost;
    QLineEdit* qPort;
    QPushButton* qConnect;

    void mqttConnect();
    void mqttDisconnect();
    void mqttSubscribe();
    void mqttMessageRX(const QByteArray &message, const QMqttTopicName &topic);
    void uiUpdate();

public:
    explicit DataManager(QObject *parent = nullptr);
    void setUI(QLineEdit* host, QLineEdit* port, QPushButton* connect);
    void setLogger(Logger* l);
    void mqttStatusReport();

signals:
    void pushData(QString head, QString value);
public slots:
    void connectButtonClicked();
    void mqttStatusChanged();

};

#endif // DATAMANAGER_H
