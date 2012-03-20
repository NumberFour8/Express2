#include "grect.h"

GRect::GRect(int ID, float Size,short sAlpha) : nID(ID), bSelected(false), fSize(Size), fDefaultSize(Size),
    Border(14,17,196,sAlpha), Body(67,179,240,sAlpha), Corner(255,0,0,sAlpha), Selected(242,10,234,sAlpha) // Hlavní barvy
{
    pPoints = new QPointF[4];
    pPoints[0].setX(-Size); pPoints[0].setY(-Size);
    pPoints[1].setX(Size);  pPoints[1].setY(-Size);
    pPoints[2].setX(Size);  pPoints[2].setY(Size);
    pPoints[3].setX(-Size); pPoints[3].setY(Size);
}

// Zresetuj útvar na výchozí polohu
void GRect::reset()
{
    pPoints[0].setX(-fDefaultSize); pPoints[0].setY(-fDefaultSize);
    pPoints[1].setX(fDefaultSize);  pPoints[1].setY(-fDefaultSize);
    pPoints[2].setX(fDefaultSize);  pPoints[2].setY(fDefaultSize);
    pPoints[3].setX(-fDefaultSize); pPoints[3].setY(fDefaultSize);
    fSize = fDefaultSize;
    bSelected = false;
}

// Konvertuje bod na vektor
Vector<float> GRect::Point2Vector(const QPointF& pt)
{
    Vector<float> Ret(3);
    Ret[0] = pt.x(); Ret[1] = pt.y(); Ret[2] = 1;
    return Ret;
}

// Transformuje útvar danou transformační maticí
void GRect::transform(const Matrix<float>& T)
{
    assert(T.getCols()==3 && T.getRows()==3);

    for (int i = 0;i < 4;++i){
        Vector<float> v = Point2Vector(pPoints[i]);
        pPoints[i] = Vector2Point(T * v);
    }

    // Přepočítej velikost
    fSize = sqrt(pow((double)(pPoints[0].x()-pPoints[1].x()),2)+pow((double)(pPoints[0].y()-pPoints[1].y()),2))/2;
}


void GRect::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget *)
{
    // Vykresli polygon
    painter->setPen(Border);
    if (bSelected)
      painter->setBrush(Selected);
    else painter->setBrush(Body);
    painter->drawPolygon(pPoints,4);

    painter->setPen(Qt::black);

    // Zjisti velikosti písma
    int w = painter->fontMetrics().width('0'), h = painter->fontMetrics().height();

    // Spočti střed úhlopříčky čtverce
    QPointF p = QPointF(pPoints[2].x()-pPoints[0].x(),pPoints[2].y()-pPoints[0].y());
    float sz = sqrt(pow(p.x(),2)+pow(p.y(),2));

    p.rx() *= sqrt(2)*fSize/sz;
    p.ry() *= sqrt(2)*fSize/sz;

    // Vypiš text
    painter->drawText(QPointF(pPoints[0].x()+p.x()-w/2,pPoints[0].y()+p.y()+h/3),QString::number(nID));

    // Vykresli kruh do pravého dolního rohu
    painter->setPen(Corner);
    painter->setBrush(Corner);
    painter->drawEllipse(pPoints[3],3,3);
}
