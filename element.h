#ifndef ELEMENT_H
#define ELEMENT_H

#include <QGraphicsPathItem>
#include <QColor>

namespace KMP_{
    enum InkType{
        IT_Pencil = 0x0000000
    };

    enum ElementPropertyType{
        EPT_Id,
        EPT_Locked,
        EPT_Visibiled,
        EPT_Color,
        EPT_Thickness,
        EPT_Layer
    };
}


class Element : public QGraphicsPathItem
{
public:
    Element(QGraphicsPathItem *parent = 0);

    void setColor( const QColor& color );
    void setThickness( int thickcness );
    void render(void);

    void addPoint( const QPointF& pt ){
        this->_listPoints.push_back(pt);
    }
    QColor color(void)const{return this->data(KMP_::EPT_Color).value<QColor>();}
    int thickness(void)const{return this->data(KMP_::EPT_Thickness).toInt();}

private:
    std::vector<QPointF> _listPoints;
};

#endif // ELEMENT_H
