#ifndef HORIZON_H
#define HORIZON_H

#include <QWidget>

class Horizon : public QWidget
{
    Q_OBJECT
public:
    explicit Horizon(QWidget *parent = nullptr);
    void setRoll(double value);
    void setPitch(double value);
protected:
    void paintEvent(QPaintEvent*) override;
private:
    double roll;
    double pitch;
    void transformPainter(QPainter &painter);

signals:

public slots:
};

#endif // HORIZON_H
