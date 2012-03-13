#ifndef GRECT_H
#define GRECT_H

#include <QGraphicsItem>
#include <QRectF>
#include <QPainter>

#include "vector.h"

class GRect : public QGraphicsItem
{
    public:
        GRect(int ID,float Size) : nID(ID), fSize(Size),pos(2), sOpacity(255) { }

        QRectF boundingRect() const { return QRectF(pos[0]-fSize,pos[1]+fSize,fSize*2,fSize*2);  }

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

        void setSelect(bool selected) { bSelected = selected; }
        bool getSelect() const { return bSelected; }

        void setID(int id) { nID = id; }
        int getID() const { return nID; }

        void setSize(float Size) { fSize = Size; }
        float getSize() const { return fSize; }


        void setAlpha(short opacity) { sOpacity = opacity; }
        short getAlpha() const { return sOpacity; }

        Vector<float>& position() { return pos; }

    private:
        int nID;
        bool bSelected;

        float fSize;
        Vector<float> pos;
        short sOpacity;

};

#endif // GRECT_H
