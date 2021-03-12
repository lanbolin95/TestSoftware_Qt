#include "element.h"
#include <QBrush>
#include <QPen>

Element::Element(QGraphicsPathItem *parent)
{

}

void Element::setColor(const QColor &color)
{
    QVariant v;
    v.setValue<QColor>(color);
    this->setData( KMP_::EPT_Color,v);
}

void Element::setThickness(int thickcness)
{
    this->setData( KMP_::EPT_Thickness,QVariant(thickcness));
}

void Element::render()
{
    if(this->_listPoints.size() < 1 ) return ;

    QPainterPath path;
    path.moveTo( this->_listPoints[0]);
    for( size_t i = 1 ; i < this->_listPoints.size() ; i++ ){
        path.lineTo( this->_listPoints[i]);
    }

    this->setPen( QPen(QBrush(color()), (qreal)thickness() , Qt::SolidLine , Qt::RoundCap,Qt::RoundJoin) );
    this->setPath( path );
}
