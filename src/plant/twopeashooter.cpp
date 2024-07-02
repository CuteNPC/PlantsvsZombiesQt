#include "plant/twopeashooter.h"
#include "include/constval.h"
#include "interface/gamewidget.h"
#include "util/bullet.h"
#include <synchapi.h>

TwoPeaShooter::TwoPeaShooter(QWidget *parent_, int y_, int x_) : Plant(parent_, y_, x_, 5)
{
    timer = new QTimer(this); // 计时器
    timer->start(plantCd[5]); // 设置计时器
    cnt = 0;                  // 计数初始化

    connect(timer, &QTimer::timeout, this,
            [=]()
            {
                if (cnt <= 1) // 0,1发射，2,3不发射
                {
                    if (((GameWidget *)parentWidget())->hasZombie(placeY))
                    {
                        ((GameWidget *)parentWidget())->bul_mutex[placeY]->lock();
                        ((GameWidget *)parentWidget())->bullets[placeY] << new Bullet(
                            50 + 100 * placeX + 70, 65 + 100 * placeY + 30, parentWidget(), 1, 0);
                        ((GameWidget *)parentWidget())->bul_mutex[placeY]->unlock();
                    }
                }
                cnt = (cnt + 1) % 4;
            });
}
