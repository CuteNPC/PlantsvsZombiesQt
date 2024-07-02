#include "util/car.h"
#include "interface/gamewidget.h"
#include <QImage>
#include <QPixmap>
#include <QRect>
#include <constval.h>

Car::Car(GameWidget *ptr, int y)
    : // 构造小推车
      QLabel((QWidget *)ptr), ani(new QPropertyAnimation(this, "geometry", (QWidget *)ptr)),
      timer(new QTimer())
{
    setGeometry(0, y, 80, 80);
    setMovie(new QMovie(trolley[0]));
    movie()->start();
    timer->setInterval(10);
    ani->setStartValue(geometry());
    ani->setEndValue(QRect(1100, y, 80, 80));
    ani->setDuration(5000);
    connect(timer, SIGNAL(timeout()), this, SLOT(try_to_kill())); // 活化以后，高频发出kill信号
    connect(
        ani, SIGNAL(finished()), this,
        SLOT(
            try_to_set_null())); // 这两行表示：小推车走完全程，命令父对象将其移除（把它的指针置空）
    connect(this, SIGNAL(set_null(int)), ptr, SLOT(delete_car(int)));
    connect(ani, SIGNAL(finished()), this, SLOT(deleteLater())); // 小推车走完全程，自动析构
    show();
    setAttribute(Qt::WA_TransparentForMouseEvents, true);
}

void Car::try_to_kill() // timeout时发出kill信号，指示自身所在位置
{
    emit kill(x());
}

void Car::try_to_set_null()
{ // 命令父对象把它的指针置空，以免出现野指针，之后生成的僵尸不再与之相关联
    emit set_null((y() - 50) / 100);
}

void Car::deleteLater() // 延时析构
{
    timer->deleteLater();
    ani->deleteLater();
    QLabel::deleteLater();
}

void Car::activate() // 每有一个僵尸到达最后一行，都会试图活化。若已经活化过了，就什么也不做
{
    if (is_active)
        return;
    is_active = 1;
    timer->start();
    ani->start();
}
