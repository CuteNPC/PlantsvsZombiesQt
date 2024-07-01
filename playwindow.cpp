#include "playwindow.h"
#include"plant.h"
#include<QDebug>
#include<QPalette>
#include<QPixmap>
#include<QDebug>
#include<QFile>
#include<QDir>
#include<qrandom.h>
#include<ctime>

Playwindow::Playwindow():mainthread(new Mainthread(this)), zomthread(new Zombiethread(this)), Suntimer(new QTimer()),
    refresh_timer(new QTimer()), zom_mutex(new QMutex()), sun_mutex(new QMutex()){

    srand(clock());
    plants[1][1] = new Plant(this, 1, 1, 10, "../framework/images/豌豆射手.gif");
    for(int i = 0;i<5;i++){
        plants[1][i] = new Plant(this, i, 1, 10, "../framework/images/豌豆射手.gif");
        bul_mutex[i] = new QMutex;
        cars[i] = new Car(this, i * 100 + 80);
    }

    setObjectName("playwindow");
    setStyleSheet("#playwindow{border-image:url(../framework/images/background.png)}");
    setGeometry(10,10,1100,600);

    Suntimer->setInterval(5000);
    refresh_timer->setInterval(1);
    connect(Suntimer, SIGNAL(timeout()), this, SLOT(new_sun()));
    connect(refresh_timer, SIGNAL(timeout()), this, SLOT(refresh()));
    mainthread->start();
    zomthread->start();
    Suntimer->start();
    refresh_timer->start();
    show();
}

void Playwindow::new_zombie(){
    zom_mutex->lock();
    int category = rand()%3;
    int loc = rand()%5;
    switch (category) {
    case 0:
        zombies[loc] << new ordinary(loc, this);
        break;
    case 1:
        zombies[loc] << new barricade(loc, this);
        break;
    case 2:
        zombies[loc] << new drums(loc, this);
        break;
    default:
        break;
    }
    zom_mutex->unlock();
}

void Playwindow::new_sun(){
    sun_mutex->lock();
    suns << new Sun(this, 1);
    sun_mutex->unlock();
}

void Playwindow::add_sun(){
    sunshine += 25;
}

void Playwindow::refresh(){
    setStyleSheet("#playwindow{border-image:url(../framework/images/background.png)}");
}

void Playwindow::exit(){

}

void Playwindow::pause(){

}

void Playwindow::delete_car(int I){
    cars[I] = nullptr;
}


