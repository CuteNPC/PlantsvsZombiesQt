#include "coldpeashooter.h"
#include "bullet.h"
#include "constval.h"
#include "gamewidget.h"
#include "peashooter.h"

//寒冰射手
ColdPeaShooter::ColdPeaShooter(QWidget* parent_, int y_, int x_)
    : Plant(parent_, y_, x_, 4)
{
    timer = new QTimer(this); //计时器 用于
    timer->start(plantCd[4]); //设置冷却时间
    //定时发子弹
    connect(timer, &QTimer::timeout, this, [=]() {
        if (((GameWidget*) parentWidget())->hasZombie(placeY)) {
            ((GameWidget*) parentWidget())->bul_mutex[placeY]->lock();
            ((GameWidget*) parentWidget())->bullets[placeY]
                << new Bullet(50 + 100 * placeX + 70, 65 + 100 * placeY + 30, parentWidget(), 1, 1);
            ((GameWidget*) parentWidget())->bul_mutex[placeY]->unlock();
        }
    });
}
