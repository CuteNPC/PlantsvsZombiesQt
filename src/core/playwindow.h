#ifndef PLAYWINDOW_H
#define PLAYWINDOW_H

#include "playthread.h"
#include"zombie.h"
#include"plant.h"
#include"bullet.h"
#include"sun.h"
#include"car.h"
#include<QVector>
#include<QQueue>
#include<QMainWindow>
#include<QMutex>
#include<QTimer>

class Playwindow:public QMainWindow
{
     Q_OBJECT
public:
    Mainthread* mainthread;
    Zombiethread* zomthread;
    QTimer* Suntimer, *refresh_timer;
    Plant* plants[9][5]={nullptr};
    QVector<Bullet*> bullets[5];
    QVector<Zombie*> zombies[5];
    QVector<Sun*> suns;
    Car* cars[5];

    Playwindow();

    QMutex* bul_mutex[5];
    QMutex* zom_mutex;
    QMutex* sun_mutex;

    int sunshine=25;

public slots:
    void pause();
    void exit();
    void new_zombie();
    void new_sun();
    void add_sun();
    void refresh();
    void delete_car(int I);
};

#endif // PLAYWINDOW_H
