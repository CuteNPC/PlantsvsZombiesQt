#include "plant/sunflower.h"
#include "include/constval.h"
#include "include/size.h"
#include "interface/gamewidget.h"
#include "util/bullet.h"
#include "util/sun.h"

SunFlower::SunFlower(QWidget *parent, int y_, int x_) : Plant(parent, y_, x_, 2)
{
    timer = new QTimer(this); // 计时器
    timer->start(plantCd[2]); // 初始化
    // 连接定时器与发射槽函数
    connect(timer, &QTimer::timeout, this,
            [=]()
            {
                new Sun((GameWidget *)parentWidget(), 0,
                        PLANT_SX + PLANT_X / 2 + PLANT_X * placeX - 50,
                        PLANT_SY + PLANT_Y * (placeY + 1) - 75);
            });
}
