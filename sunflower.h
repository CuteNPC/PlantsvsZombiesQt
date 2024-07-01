#ifndef SUNFLOWER_H
#define SUNFLOWER_H

#include "plant.h"
#include <QWidget>

//向日葵

class SunFlower : public Plant
{
    Q_OBJECT
    QTimer * timer;//向日葵计时器
public:
    SunFlower(QWidget* parent,int y_,int x_);
};

#endif // SUNFLOWER_H
