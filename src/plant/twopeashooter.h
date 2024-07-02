#ifndef TWOPEASHOOTER_H
#define TWOPEASHOOTER_H

#include "plant.h"
#include <QWidget>

//双枪射手

class TwoPeaShooter : public Plant
{
    Q_OBJECT
    QTimer* timer;//计时器
    int cnt; //4次一组，用来计算是计时器第几次响应，第一二次发射，三四次不发射

public:
    TwoPeaShooter(QWidget* parent,int y_,int x_);
};

#endif // TWOPEASHOOTER_H
