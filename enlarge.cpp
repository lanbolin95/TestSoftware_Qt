#include "enlarge.h"
#include "ui_enlarge.h"
#include <QScreen>
#include <QPainter>
#include <QWindow>

enlarge::enlarge(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::enlarge)
{
    ui->setupUi(this);
    setFixedSize(400, 400);
    Qt::WindowFlags flags= this->windowFlags();
    setWindowFlags(flags&~Qt::WindowContextHelpButtonHint);
}

enlarge::~enlarge()
{
    delete ui;
}

void enlarge::Enlarge()
{
    int x = QCursor::pos().x();
    int y = QCursor::pos().y();
    QWindow *window = windowHandle();
    QScreen *screen = window->screen();
    QPixmap pixmap = screen->grabWindow(0);
    QPixmap pix = pixmap.copy(x - 100, y - 100, 200, 200);
    QPixmap fitPixmap = pix.scaled(400, 400, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    ui->label->setPixmap(fitPixmap);
}
