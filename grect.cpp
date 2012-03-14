#include "grect.h"

GRect::GRect(int ID, float Size) : nID(ID), fSize(Size), sOpacity(255)
{
    pPoints = new QPointF[4];
    pPoints[0].setX(-Size); pPoints[0].setY(-Size);
    pPoints[1].setX(Size);  pPoints[1].setY(-Size);
    pPoints[2].setX(Size);  pPoints[2].setY(Size);
    pPoints[3].setX(-Size); pPoints[3].setY(Size);

}

GRect::~GRect()
{
    delete[] pPoints;
}

Vector<float> GRect::Point2Vector(const QPointF& pt)
{
    Vector<float> Ret(3);
    Ret[0] = pt.x(); Ret[1] = pt.y(); Ret[2] = 1;
    return Ret;
}

void GRect::transform(const Matrix<float>& T)
{
    for (int i = 0;i < 4;++i){
        Vector<float> v = Point2Vector(pPoints[i]);
        pPoints[i] = Vector2Point(T * v);
    }
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
