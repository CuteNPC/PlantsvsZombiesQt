#include "sunflower.h"
#include "bullet.h"
#include "constval.h"
#include "gamewidget.h"
#include "size.h"
#include "sun.h"

SunFlower::SunFlower(QWidget* parent, int y_, int x_)
    : Plant(parent, y_, x_, 2)
{
    timer = new QTimer(this); //计时器
    timer->start(plantCd[2]); //初始化
    //连接定时器与发射槽函数
    connect(timer, &QTimer::timeout, this, [=]() {
        new Sun((GameWidget*) parentWidget(),
                0,
                PLANT_SX + PLANT_X / 2 + PLANT_X * placeX - 50,
                PLANT_SY + PLANT_Y * (placeY + 1) - 75);
    });
}
