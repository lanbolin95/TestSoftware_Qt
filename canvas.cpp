#include "canvas.h"

Canvas::Canvas(QObject *parent) : QGraphicsScene(parent)
{
    this->_isDrawing =false;
}

void Canvas::onDeviceDown(const QPointF &pt, int id)
{
    if(_itemMap.keys().contains(id))
    {
        InkDData* dt = _itemMap.value(id);
        if(dt->element)
            removeItem(dt->element);
        if(dt->TempDrawingItem.size() >= 1 ){
            for(size_t i = 0; i < dt->TempDrawingItem.size() ;i++)
            {
                removeItem(dt->TempDrawingItem[i]);
            }
        }

        dt->TempDrawingItem.clear();
        delete dt;

         _itemMap.remove( id );
    }

    InkDData* dt =  new InkDData;
    dt->prePoint = pt;//scene point;
    dt->element  = new Element;
    dt->element->addPoint(pt);
    _itemMap.insert( id , dt );

    this->drawStart( dt );
}

void Canvas::onDeviceMove(const QPointF &pt, int id)
{
    if(_itemMap.keys().contains(id)){
        InkDData* dt = _itemMap.value(id);
        QPointF to = pt;

        if(dt->element)
            dt->element->addPoint( to );

        this->drawTo( dt , to );
        dt->prePoint = to;
    }
}

void Canvas::onDeviceUp(int id)
{
    if(_itemMap.keys().contains(id)){
        InkDData* dt = _itemMap.value(id);
        for(size_t i = 0; i < dt->TempDrawingItem.size() ;i++)
        {
            removeItem( dt->TempDrawingItem[i]);
        }

        dt->TempDrawingItem.clear();
        dt->element->setColor( _inkColor );
        dt->element->setThickness( _inkThickness );
        dt->element->render();
        addItem(  dt->element );

        _itemMap.remove( id );
    }
}

void Canvas::drawStart(InkDData *dt)
{
    double x = dt->prePoint.x() - (double(_inkThickness)/2.f);
    double y = dt->prePoint.y() -(double(_inkThickness)/2.f);

    QGraphicsEllipseItem* el = addEllipse(QRect(x,y,_inkThickness,_inkThickness),
                                          QPen(_inkColor,1 ) , QBrush(_inkColor));

    dt->TempDrawingItem.push_back(el);
}

void Canvas::drawTo(InkDData *dt, const QPointF &to)
{
    QGraphicsLineItem* li = addLine(dt->prePoint.x(),
                                    dt->prePoint.y(),
                                    to.x(),to.y(),
                                    QPen(QBrush(_inkColor),_inkThickness,Qt::SolidLine,
                                         Qt::RoundCap,Qt::RoundJoin ));

    dt->TempDrawingItem.push_back(li);
}
