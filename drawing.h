#ifndef DRAWING_H
#define DRAWING_H

#include <QWidget>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QMouseEvent>
#include "canvas.h"

namespace Ui {
class Drawing;
}

class Drawing : public QGraphicsView
{
    Q_OBJECT

public:
    explicit Drawing(QWidget *parent = 0);
    ~Drawing();

    void setInkColor(const QColor* color );
    void setInkThickness(int thickness );
    Canvas* currentSlide(void)const{return this->_currentSlide; }
    void setScene(Canvas *scene);
    void mouseMenu();

protected:
    void keyPressEvent(QKeyEvent *e);
    void mousePressEvent(QMouseEvent *e);
    bool viewportEvent(QEvent *event);

private:
    Ui::Drawing *ui;

    Canvas *mCanvas;
    Canvas *_currentSlide;
    bool _isTouchMode;

Q_SIGNALS:
    void slideChangedBefore(void);
    void slideChangedAfter(void);
};

#endif // DRAWING_H
