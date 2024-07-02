#include "util/sun.h"
#include "interface/gamewidget.h"
#include <QEasingCurve>
#include <QRect>
#include <QTimer>
#include <cmath>
#include <ctime>
#include <qrandom.h>

Sun::Sun(GameWidget *p, bool is_nature, int x, int y)
    : QLabel((QWidget *)p), parent(p), renewer(new QTimer())
{
    setMouseTracking(1);
    setAlignment(Qt::AlignCenter);
    // ani1下落动画初始化
    ani1 = new QPropertyAnimation(this, "geometry", p);
    ani2 = new QPropertyAnimation(this, "geometry", p);

    // 设置gif动画
    movie = new QMovie(":/resources/images/sun.gif");
    setMovie(movie);
    movie->start();

    // 设置消失定时器
    timer = new QTimer();
    timer->setInterval(10000);
    timer->setSingleShot(1);
    connect(timer, SIGNAL(timeout()), this, SLOT(deleteLater()));

    // 设置被采集的动画
    connect(ani2, &QPropertyAnimation::finished, [=]() { parent->addSun(25); });
    connect(ani2, SIGNAL(finished()), this, SLOT(deleteLater()));

    renewer->setInterval(100);
    connect(renewer, SIGNAL(timeout()), this, SLOT(raise()));

    show();

    if (is_nature) // 自然生成的阳光，随机设置列数和下落点
    {
        x = rand() % (p->width() - 100);
        setGeometry(x, 1, 100, 100);
        ani1->setStartValue(geometry());
        y = rand() % p->height();
        ani1->setEndValue(QRect(x, y, 100, 100));
        ani1->setDuration((y - 1) * 20);
        connect(ani1, SIGNAL(finished()), timer, SLOT(start()));
        ani1->start();
    }
    else // 向日葵生成的阳光，直接指定位置
    {
        setGeometry(x, y, 100, 100);
        timer->start();
    }
    setWindowOpacity(0);
    setWindowFlags(Qt::FramelessWindowHint);
    renewer->start();
    show();
}

void Sun::deleteLater() // 延时析构
{
    movie->deleteLater();
    ani1->deleteLater();
    ani2->deleteLater();
    timer->deleteLater();
    renewer->deleteLater();
    QLabel::deleteLater();
}

void Sun::mousePressEvent(QMouseEvent *event) // 点击时收集
{
    timer->stop();

    ani1->stop();

    ani2->setStartValue(geometry());
    ani2->setEndValue(QRect(10, 10, 100, 100));
    ani2->setDuration(fmin(sqrt((x() - 10) * (x() - 10) + (y() - 10) * (y() - 10)) * 3, 1000));
    ani2->setEasingCurve(QEasingCurve::OutQuad);
    ani2->start();
}

void Sun::mouseMoveEvent(QMouseEvent *ev)
{
    ((GameWidget *)parentWidget())->tryMove(ev->position().x() + x(), ev->position().x() + y());
}
