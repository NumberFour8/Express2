#include "grect.h"

void GRect::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget *)
{
    QColor Border(112,27,224);
    QColor Body(67,179,240);
    QColor Pink(227,175,226);

    painter->setPen(Border);
    painter->fillRect(boundingRect(),Body);
    painter->drawRect(boundingRect());

    painter->setPen(Pink);
    painter->setBrush(Pink);
    painter->drawEllipse(QPointF(pos[0]+fSize,pos[1]-fSize),5,5);

}
