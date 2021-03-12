#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QGraphicsScene>
#include <QMap>
#include <QColor>
#include "element.h"

struct InkDData{
    QPointF prePoint;
    std::vector<QGraphicsItem*> TempDrawingItem;
    Element* element;
    InkDData(){
        this->element = Q_NULLPTR;
        this->TempDrawingItem .clear();
    }
};

class Canvas : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Canvas(QObject *parent = nullptr);

    void setColor(const QColor& color ){this->_inkColor = color;}
    void setThickness(int w ){this->_inkThickness = w ;}
    void onDeviceDown( const QPointF& pt , int id = 0);
    void onDeviceMove( const QPointF& pt , int id = 0);
    void onDeviceUp( int id );
    void drawStart( InkDData* dt );
    void drawTo( InkDData* dt , const QPointF& to );
    bool _isDrawing;

signals:

public slots:

private:
    QGraphicsScene *GraphicsScene;
    QPoint startPos;
    QPoint endPos;

    int _inkThickness;
    QColor _inkColor;
    QMap< int , InkDData* > _itemMap;
};

#endif // CANVAS_H
