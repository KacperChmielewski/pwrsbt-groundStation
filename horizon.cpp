#include "horizon.h"

#include <QPainter>

Horizon::Horizon(QWidget *parent) : QWidget(parent)
{

}

void Horizon::paintEvent(QPaintEvent*)
{
    QPainter* painter = new QPainter(this);

    // Background
    QBrush background(QColor(0, 180, 255));
    painter->setBrush(background);
    painter->drawRect(0, 0, width(), height());

    int w = width();
    int h = height() / 2;


    QBrush earth(QColor(200, 80, 20));
    painter->setBrush(earth);
    QRect rect(0, height()/2, w, h);
    painter->drawRect(rect);

    painter->rotate(60);
    painter->save();
}

void Horizon::transformPainter(QPainter &painter)
{
    painter.rotate(60);
}
