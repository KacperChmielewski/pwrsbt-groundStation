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


    QBrush background(QColor(0, 180, 255));
    QBrush earth(QColor(200, 80, 20));
    QBrush arrow(QColor(200, 150, 0));

    // Background

    painter->setBrush(background);
    painter->drawRect(0, 0, width(), height());

    int w = width()*4;
    int h = height()*2;

    painter->setBrush(earth);

    double heightPitchFactor = pitch / 60 / 2;

    painter->translate(width()/2, height()/2 + heightPitchFactor*height());
    painter->rotate(roll);

    QRect rect(-width()*2, 0, w, h);

    double yawFactor = height()/12;

    painter->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));
    painter->drawRect(rect);






    painter->rotate(-roll);

    painter->setPen(QPen(Qt::white, 1, Qt::SolidLine, Qt::RoundCap));

    for (int i = -5; i < 6; ++i) {
        int lineY = yawFactor * i;
        painter->drawLine(QPoint(-width()/4, lineY), QPoint(width()/4, lineY));
    }

    painter->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));


    painter->translate(0, - heightPitchFactor*height());



    int baseW = width()/5;
    int baseH = width()/10;

    painter->setBrush(arrow);

    QPolygon centerArrow;
    centerArrow << QPoint(-baseW, baseH) << QPoint(0, baseH*2/3) << QPoint(baseW, baseH) << QPoint(0, 0);
    painter->drawPolygon(centerArrow);


    baseW = width()/10;
    baseH = width()/30;

    painter->translate(-width()/3, 0);
    QPolygon sideArrow;
    sideArrow << QPoint(-baseW, baseH) << QPoint(-baseW, -baseH) << QPoint(0, -baseH) << QPoint(baseW/3, 0) << QPoint(0, baseH);
    painter->drawPolygon(sideArrow);

    painter->translate(width()/3, 0);
    painter->translate(width()/3, 0);
    painter->rotate(180);
    painter->drawPolygon(sideArrow);




}

void Horizon::setRoll(double value) {
    roll = value;
    update();
}

void Horizon::setPitch(double value) {
    pitch = value;
}
