#ifndef HORIZON_H
#define HORIZON_H

#include <QWidget>

class Horizon : public QWidget
{
    Q_OBJECT
public:
    explicit Horizon(QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent*) override;
private:
    void transformPainter(QPainter &painter);

signals:

public slots:
};

#endif // HORIZON_H
