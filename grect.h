#ifndef GRECT_H
#define GRECT_H

#include <QGraphicsItem>
#include <QRectF>
#include <QPainter>
#include <QPointF>

#include "vector.h"
#include "matrix.h"

class GRect : public QGraphicsItem
{
    public:
        GRect(int ID,float Size,short sAlpha = 255);
        ~GRect() { delete[] pPoints; }

        QRectF boundingRect() const { return QRectF(pPoints[0].x(),pPoints[0].y(),fSize*2,fSize*2);  }

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

        void reset();

        void selectMe(bool select) { bSelected = select; }

        void transform(const Matrix<float>& T);

        static Vector<float> Point2Vector(const QPointF& pt);
        static QPointF Vector2Point(const Vector<float>& v) { return QPointF(v[0],v[1]); }

    private:
        int nID;
        bool bSelected;

        float fSize;
        const float fDefaultSize;

        QPointF *pPoints;

        QColor Border,Body,Corner,Selected;
};

#endif // GRECT_H
