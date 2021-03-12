#include "drawing.h"
#include "ui_drawing.h"
#include <QMenu>
#include <QEvent>
#include <QTouchEvent>

Drawing::Drawing(QWidget *parent) :
    QGraphicsView(parent)
{
    this->showFullScreen();
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setInteractive(true);
    this->setOptimizationFlag(QGraphicsView::IndirectPainting);
    this->setCacheMode(QGraphicsView::CacheBackground);

    //for touch
    this->setAttribute(Qt::WA_AcceptTouchEvents);
    this->viewport()->setAttribute(Qt::WA_AcceptTouchEvents);

    //antialiasing
    setRenderHint(QPainter::Antialiasing,true );

    //init scene
    Canvas* slide = new Canvas;
    this->setScene(slide);
    this->setSceneRect(0,0,600,600);
//    this->resize( 600,600);

    slide->setColor(Qt::red);
    slide->setThickness( 4 );

    this->_currentSlide = slide;
}

Drawing::~Drawing()
{
    delete ui;
}

void Drawing::setScene(Canvas *scene)
{
    Q_EMIT slideChangedBefore();
    QGraphicsView::setScene( scene );
    this->_currentSlide = scene;

    Q_EMIT slideChangedAfter();
}

void Drawing::keyPressEvent(QKeyEvent *e)
{
    switch (e->key()) {
    case Qt::Key_Escape:
        this->close();
        break;
    case Qt::Key_C:
        _currentSlide->clear();
        break;
    default:
        break;
    }
}

void Drawing::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::RightButton)
    {
        mouseMenu();
    }
}

void Drawing::mouseMenu()
{
    //创建菜单对象
    QMenu *pMenu = new QMenu(this);

    QAction *pClearTask = new QAction(tr("清除"), this);
    QAction *pExitTask = new QAction(tr("退出"), this);

    //1:清除 2:退出
    pClearTask->setData(1);
    pExitTask->setData(2);

    //把QAction对象添加到菜单上
    pMenu->addAction(pClearTask);
    pMenu->addAction(pExitTask);

    //连接鼠标右键点击信号
    connect(pClearTask, SIGNAL(triggered()), _currentSlide, SLOT(clear()));
    connect(pExitTask, SIGNAL(triggered()), this, SLOT(close()));

    //在鼠标右键点击的地方显示菜单
    pMenu->exec(cursor().pos());

    //释放内存
    QList<QAction*> list = pMenu->actions();
    foreach (QAction* pAction, list) delete pAction;
    delete pMenu;
}

bool Drawing::viewportEvent(QEvent *event)
{
    // 处理touch事件
    QEvent::Type evType = event->type();
    if(evType == QEvent::TouchBegin || evType == QEvent::TouchUpdate || evType == QEvent::TouchEnd )
    {
        QTouchEvent* touchEvent = static_cast<QTouchEvent*>(event);
        QList<QTouchEvent::TouchPoint> touchPoints = touchEvent->touchPoints();

        foreach( const QTouchEvent::TouchPoint tp , touchPoints ){
            //不考虑pad
            QPoint touchPos  = QPoint( tp.pos().x() , tp.pos().y() );
            if(tp.id() == 0 ){
                if( tp.state() == Qt::TouchPointPressed )
                    this->_isTouchMode = true;
                else
                    this->_isTouchMode = false;
            }

            QPointF scenepos = this->mapToScene(touchPos.x() , touchPos.y() );
            switch( tp.state() )
            {
            case Qt::TouchPointPressed:
                this->_currentSlide->onDeviceDown(scenepos, tp.id());
                break;
            case Qt::TouchPointMoved:
                this->_currentSlide->onDeviceMove(scenepos,tp.id());
                break;
            case Qt::TouchPointReleased:
                this->_currentSlide->onDeviceUp(tp.id());
                break;
            case Qt::TouchPointStationary:
                break;
            }
        }

        if(evType == QEvent::TouchEnd ){
            // to do
        }

        return true;
    }

    return QGraphicsView::viewportEvent(event);
}
