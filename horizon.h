/*!
* \file
* \brief Definicja klasy widgetu sztucznego horyzontu
*
* Plik zawiera definicję klasy Horizon
*/

#ifndef HORIZON_H
#define HORIZON_H

#include <QWidget>

/*!
* \brief Widget sztucznego horyzontu
*
* Klasa jest widgetem, który rysuje sztuczny horyzont.
*/
class Horizon : public QWidget
{
    Q_OBJECT
public:
    explicit Horizon(QWidget *parent = nullptr);
    /*!
     * \brief Ustawianie przechylenia
     *
     * Uaktualnia wartość przechylenia i ponownie rysuje widget
     * \param[in] value - wartość kąta
     */
    void setRoll(double value);
    /*!
     * \brief Ustawianie pochylenia
     *
     * Uaktualnia wartość pochylenia i ponownie rysuje widget
     * \param[in] value - wartość kąta
     */
    void setPitch(double value);
protected:
    /*!
     * \brief Zdarzenie rysowania
     *
     * Metoda definiuje sposób rysowania widgetu
     */
    void paintEvent(QPaintEvent*) override;
private:
    /*!
     * \brief Ustawianie pochylenia
     *
     * Uaktualnia wartość pochylenia i ponownie rysuje widget
     * \param[in] value - wartość kąta
     */
    double roll;
    double pitch;
};

#endif // HORIZON_H
