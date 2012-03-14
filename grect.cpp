#include "grect.h"

GRect::GRect(int ID, float Size) : nID(ID), fSize(Size), sOpacity(255)
{
    pPoints = new QPointF[4];
    pPoints[0] = QPoint(-Size,-Size);
    pPoints[1] = QPointF(Size,-Size);
    pPoints[2] = QPointF(Size,Size);
    pPoints[3] = QPointF(-Size,Size);

}

GRect::~GRect()
{
    delete[] pPoints;
}

void GRect::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget *)
{
    QColor Border(112,27,224,sOpacity);
    QColor Body(67,179,240,sOpacity);
    QColor Corner(255,0,0,sOpacity);

    painter->setPen(Border);
    painter->setBrush(Body);
    painter->drawPolygon(pPoints,4);

    painter->setPen(Qt::black);
    painter->drawText(QRectF(pPoints[0].x()+4*fSize/5,pPoints[0].y()+3*fSize/5,fSize,fSize),QString::number(nID));

    painter->setPen(Corner);
    painter->setBrush(Corner);
    painter->drawEllipse(pPoints[0],3,3);
}
