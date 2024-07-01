#include "bullet.h"
#include"gamewidget.h"
#include"zombie.h"
#include<QRect>
#include<QString>
#include<QPicture>
#include<QImage>
#include<QPixmap>
#include"constval.h"
#include"qrandom.h"
#include<gamewidget.h>


Bullet::Bullet(int x,int y, QWidget* ptr, int a,bool b):QLabel(ptr),attack(a), is_debuff(b),mutex(new QMutex()),
    ani(new QPropertyAnimation(this, "geometry", (QWidget*)ptr)), timer(new QTimer)
{   //参数从左到右依次是：生成时的x坐标，生成时的y坐标，父对象指针，攻击力，是否有减速效果

    setAttribute(Qt::WA_TransparentForMouseEvents, true);

    //析构
    connect(ani, SIGNAL(finished()), this, SLOT(to_be_deleted()));
    connect(this, SIGNAL(shut_down()), this, SLOT(crash()));

    //设置计时器
    timer->setInterval(1000);
    timer->setSingleShot(1);

    //设置图片
    setPixmap(QPixmap::fromImage(bulletQImg[b]));
    setGeometry(x,y,30,30);
    setScaledContents(true);//填充显示

    //设置动画
    ani->setStartValue(geometry());
    ani->setEndValue(QRect(1300, y, 30,30));
    ani->setDuration((1300-x)*2);
    show();
    ani->start();
}

void Bullet::deleteLater()                  //延时析构
{
    is_dead = 1;
    timer->deleteLater();
    movie()->deleteLater();
    ani->deleteLater();
    QLabel::deleteLater();
}

void Bullet::to_be_deleted(){           //告知父对象将从队列中移除，以免出现野指针
    is_dead = 1;
}

void Bullet::crash()                        //碰到僵尸，设置炸裂动画，炸裂完毕自动析构
{
    setMovie(new QMovie(bulletImg[2]));
    movie()->start();
    connect(movie(), SIGNAL(finished()), this, SLOT(deleteLater()));
}
