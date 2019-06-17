/*!
* \file
* \brief Definicja klasy dziennika zdarzeń
*
* Plik zawiera definicję klasy Logger
*/
#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>

#include <QPlainTextEdit>
#include <QPushButton>
/*!
* \brief Obsługa dziennika zdarzeń
*
* Klasa jest obsługuje elementy dziennika zdarzeń i udostępnia
* metody jego obsługi.
*/
class Logger : public QObject
{
    Q_OBJECT
private:
    QPlainTextEdit* textEdit;
    QPushButton* button;
public:
    explicit Logger(QObject *parent = nullptr);
    /*!
     * \brief Przypisanie elementów interfejsu
     *
     * Podpina elementy interfejsu, które będą używane jako dziennik zdarzeń
     * \param[in] txt - okno loggera
     * \param[in] btn - przycisk kasujący dane
     */
    void setUI(QPlainTextEdit *txt, QPushButton *btn);
    /*!
     * \brief Pisanie do loggera
     *
     * Drukuje podany ciąg w oknie dziennika zdarzeń
     * \param[in] text - dane do wydrukowania
     */
    void print(QString text);
    /*!
     * \brief Pisanie do loggera
     *
     * Drukuje podany ciąg w oknie dziennika zdarzeń
     * \param[in] text - dane do wydrukowania
     */
    void print(const char* text);
    /*!
     * \brief Czyszczenie
     *
     * Czyszczenie okna dziennika zdarzeń
     */
    void clean();
signals:

public slots:
    /*!
     * \brief Obsługa kliknięcia "clean"
     *
     * Obsługuje zdarzenie kliknięcia "clean"
     */
    void cleanButtonClicked();
};

#endif // LOGGER_H
