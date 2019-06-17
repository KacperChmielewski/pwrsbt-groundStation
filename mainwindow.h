/*!
* \file
* \brief Definicja klasy głównego okna
*
* Plik zawiera definicję klasy MainWindow
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <logger.h>


namespace Ui {
class MainWindow;
}

/*!
* \brief Główne okno
*
* Klasa jest odpowiedzialna za rysowanie interfejsu.
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    /*!
     * \brief Slot otrzymania danych
     *
     * Slot do otrzymywania danych z serwera. Dane otrzymywa są w postaci nagłowka i wartości.
     * Następnie odpowiednia wielkości są przezentowane na interfejsie w odpowiednich miejscach
     * \param[in] head - nagłówek danych
     * \param[in] value - dane
     */
    void rxData(QString head, QString value);
private:
    Ui::MainWindow *ui;
    Logger* log;
};

#endif // MAINWINDOW_H
