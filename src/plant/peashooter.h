#ifndef PEASHOOTER_H
#define PEASHOOTER_H

#include "plant.h"
#include <QWidget>

class PeaShooter : public Plant
{
    Q_OBJECT
    QTimer* timer;//计时器

public:
    PeaShooter(QWidget* parent,int y_,int x_);
};

#endif // PEASHOOTER_H
