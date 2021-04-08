#ifndef ENLARGE_H
#define ENLARGE_H

#include <QDialog>

namespace Ui {
class enlarge;
}

class enlarge : public QDialog
{
    Q_OBJECT

public:
    explicit enlarge(QWidget *parent = 0);
    ~enlarge();

    void Enlarge();
private:
    Ui::enlarge *ui;
};

#endif // ENLARGE_H
