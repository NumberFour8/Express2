#ifndef GRECT_H
#define GRECT_H

#include <QGraphicsItem>
#include <QRectF>
#include <QPainter>
#include <QPointF>

#include "vector.h"

class GRect : public QGraphicsItem
{
    public:
        GRect(int ID,float Size);
        ~GRect();

        QRectF boundingRect() const { return QRectF(pPoints[0].x(),pPoints[0].y(),fSize*2,fSize*2);  }

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

        void setSelect(bool selected) { bSelected = selected; }
        bool getSelect() const { return bSelected; }

        void setID(int id) { nID = id; }
        int getID() const { return nID; }

        void setSize(float Size) { fSize = Size; }
        float getSize() const { return fSize; }


        void setAlpha(short opacity) { sOpacity = opacity; }
        short getAlpha() const { return sOpacity; }

        static Vector<float> Point2Vector(const QPointF& pt)
        {
            Vector<float> Ret(2);
            Ret[0] = pt.x(); Ret[1] = pt.y();
            return Ret;
        }

    private:
        int nID;
        bool bSelected;

        float fSize;
        QPointF *pPoints;
        short sOpacity;

};

#endif // GRECT_H
