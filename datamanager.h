#ifndef DATAMANAGER_H
#define DATAMANAGER_H


#include <QObject>

#include <QMqttClient>

#include <QLineEdit>
#include <QPushButton>

#include "logger.h"

class dataManager : public QObject
{
    Q_OBJECT
private:
    QMqttClient* mClient;
    logger* log;
    QLineEdit* qHost;
    QLineEdit* qPort;
    QPushButton* qConnect;

    void mqttConnect();

public:
    explicit dataManager(QObject *parent = nullptr);
    void setUI(QLineEdit* host, QLineEdit* port, QPushButton* connect);
    void setLogger(logger* l);
    void mqttStatusReport();

signals:
public slots:
    void connectButtonClicked();
    void mqttStatusChanged();

};

#endif // DATAMANAGER_H
