/*!
* \file
* \brief Definicja klasy menedżera danych
*
* Plik zawiera definicję klasy DataManager
*/

#ifndef DATAMANAGER_H
#define DATAMANAGER_H


#include <QObject>

#include <QMqttClient>

#include <QLineEdit>
#include <QPushButton>

#include "logger.h"
/*!
* \brief Zarządca danych
*
* Klasa jest odpowiedzialna za odbiór danych.
*/
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
    /*!
     * \brief Przypisanie elementów interfejsu
     *
     * Podpina elementy interfejsu, które będą używane jako konfiguracja zarządcy danych
     * \param[in] host - okno hosta
     * \param[in] port - okno portu
     * \param[in] connect - przycisk do połączenia
     */
    void setUI(QLineEdit* host, QLineEdit* port, QPushButton* connect);
    /*!
     * \brief Podpięcie loggera
     *
     * Podpina dziennik zdarzeń do zdarzeń z zarządcy danych
     * \param[in] l - wskaźnik do loggera
     */
    void setLogger(Logger* l);
    /*!
     * \brief Informacje o połączeniu
     *
     * Drukuje na dzienniku zdarzeń aktualne informacje o połączeniu z serwerem danych
     */
    void mqttStatusReport();

signals:
    /*!
     * \brief Sygnał otrzymania danych
     *
     * Sygnal wysyłany po otrzymaniu danych z serwera. Dane przesyłane są w postaci nagłowka i wartości.
     * \param[in] head - nagłówek danych
     * \param[in] value - dane
     */
    void pushData(QString head, QString value);
public slots:
    /*!
     * \brief Obsługa kliknięcia "Connect"
     *
     * Obsługuje zdarzenie kliknięcia "Connect"
     */
    void connectButtonClicked();
    /*!
     * \brief Obsługa zmiany stanu połączenia
     *
     * Obsługuje zdarzenie zmiany stanu połączenia z serwerem danych
     */
    void mqttStatusChanged();

};

#endif // DATAMANAGER_H
