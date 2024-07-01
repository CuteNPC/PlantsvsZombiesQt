#ifndef COLDPEASHOOTER_H
#define COLDPEASHOOTER_H

#include "plant.h"
#include <QWidget>

//寒冰射手
class ColdPeaShooter : public Plant
{
    Q_OBJECT
    QTimer* timer;//计时器
public:
    ColdPeaShooter(QWidget* parent,int y_,int x_);
};

#endif // COLDPEASHOOTER_H
