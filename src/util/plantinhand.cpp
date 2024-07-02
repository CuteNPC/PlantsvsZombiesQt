#include "util/plantinhand.h"
#include "interface/gamewidget.h"
#include <QDebug>
#include <QMouseEvent>
PlantInHand::PlantInHand(QWidget *parent, int id0_, QString path) : QLabel(parent)
{
    setScaledContents(true);
    id = id0_;
    resize(80, 100);
    move(200, 200);
    pixmap = QPixmap(path);
    setPixmap(pixmap);
    show();
    setAttribute(Qt::WA_TransparentForMouseEvents, true);
    raise();
}
