#include "horizon.h"

#include <QPainter>

Horizon::Horizon(QWidget *parent) : QWidget(parent)
{
    roll = 0;
    pitch = 0;
}

void Horizon::paintEvent(QPaintEvent*)
{
    QPainter* painter = new QPainter(this);

    // Background
    QBrush background(QColor(0, 180, 255));
    painter->setBrush(background);
    painter->drawRect(0, 0, width(), height());

    int w = width()*2;
    int h = height()*2;



    QBrush earth(QColor(200, 80, 20));
    painter->setBrush(earth);


    double heightPitchFactor = pitch / 60 / 2;

    painter->translate(width()/2, height()/2 + heightPitchFactor*height());
    painter->rotate(roll);

    QRect rect(-width(), 0, w, h);
    painter->drawRect(rect);




}

void Horizon::setRoll(double value) {
    roll = value;
    update();
}

void Horizon::setPitch(double value) {
    pitch = value;
}
