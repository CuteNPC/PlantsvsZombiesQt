#include "util/piconhand.h"
#include "interface/gamewidget.h"
#include <QMouseEvent>

PicOnHand::PicOnHand(QWidget *parent, QString path) : QLabel(parent)
{
    setScaledContents(true);
    resize(80, 100);
    move(200, 200);
    pixmap = QPixmap(path);
    setPixmap(pixmap);
    show();
    setAttribute(Qt::WA_TransparentForMouseEvents, true);
    raise();
}
