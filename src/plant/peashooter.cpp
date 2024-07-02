#include "plant/peashooter.h"
#include "include/constval.h"
#include "interface/gamewidget.h"
#include "util/bullet.h"
PeaShooter::PeaShooter(QWidget *parent_, int y_, int x_) : Plant(parent_, y_, x_, 1)
{
    timer = new QTimer(this); // 计时器 用于
    timer->start(plantCd[1]);
    connect(timer, &QTimer::timeout, this,
            [=]()
            {
                if (((GameWidget *)parentWidget())->hasZombie(placeY))
                {
                    ((GameWidget *)parentWidget())->bul_mutex[placeY]->lock();
                    ((GameWidget *)parentWidget())->bullets[placeY] << new Bullet(
                        50 + 100 * placeX + 70, 65 + 100 * placeY + 30, parentWidget(), 1, 0);
                    ((GameWidget *)parentWidget())->bul_mutex[placeY]->unlock();
                }
            });
}
