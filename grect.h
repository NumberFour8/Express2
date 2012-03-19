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
        ~GRect();

        QRectF boundingRect() const { return QRectF(pPoints[0].x(),pPoints[0].y(),fSize*2,fSize*2);  }

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

        void setSelect(bool selected) { bSelected = selected; }
        bool getSelect() const { return bSelected; }

        void reset();

        void setID(int id) { nID = id; }
        int getID() const { return nID; }

        void setSize(float Size) { fSize = Size; }
        float getSize() const { return fSize; }

        void transform(const Matrix<float>& T);

        static Vector<float> Point2Vector(const QPointF& pt);
        static QPointF Vector2Point(const Vector<float>& v) { return QPointF(v[0],v[1]); }

    private:
        int nID;
        bool bSelected;

        float fSize;
        const float fDefaultSize;

        QPointF *pPoints;

        QColor Border;
        QColor Body;
        QColor Corner;
};

#endif // GRECT_H
