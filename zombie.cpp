#include "zombie.h"
#include "gamewidget.h"
#include"playthread.h"
#include"bullet.h"
#include"constval.h"
#include<QPixmap>
#include<QImage>

once_movie::once_movie(QString s):QMovie(s){          //自定义的movie，每播放一轮发出一次once_finished信号
    connect(this, SIGNAL(frameChanged(int)), this, SLOT(check_if_finished(int)));
}

void once_movie::check_if_finished(int frameNumber){
    if(frameNumber == frameCount() - 1)
        emit once_finished();
}


Zombie::Zombie(int loc, double fs, double a, double sp, float es, int st, QString* movie_names, QString* eat_movie_names, GameWidget* ptr):
    QLabel((QWidget*)ptr), strength(fs), full_strength(fs), attack(a), speed(sp),  state_number(st), parent(ptr),mutex(new QMutex()),
    movs(new once_movie*[state_number]{nullptr}), eat_movs(new once_movie*[state_number]{nullptr}),
    state_now(0), eating(new QTimer()), debuff(new QTimer()), ani(new QPropertyAnimation(this, "geometry", (QWidget*)ptr)){
    //参数从左到右依次是：所在行数，血量上限，攻击力，速度，攻击频数，阶段数，各阶段动画，阶段间的切换动画，攻击时的动画，托管方

    setAttribute(Qt::WA_TransparentForMouseEvents, true);

    debuff->setInterval(2000);
    debuff->setSingleShot(1);
    eating->setInterval(es * 100);

    for(int i = 0;i<state_number; i++)                              //设置各种动画
        movs[i] = new once_movie(movie_names[i]);
    for(int i = 0;i<state_number; i++)
        eat_movs[i] = new once_movie(eat_movie_names[i]);

    setGeometry(1050, loc*100 + 40,200,150);                        //设置起始位置和运动轨迹
    setMovie(movs[0]);
    ani->setDuration(100 * (x() - 0) / speed);
    ani->setStartValue(geometry());
    ani->setEndValue(QRect(0, loc*100 + 40,200,150));
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowOpacity(0);

    connect(eating, SIGNAL(timeout()), this, SLOT(attack_enemy()));             //链接各种信号和槽
    connect(debuff, SIGNAL(timeout()), this, SLOT(recover_from_debuff()));
    connect(this, SIGNAL(change_state()), this, SLOT(change_to_formal_state()));
    connect(this, SIGNAL(move()), this, SLOT(move_forward()));
    connect(this, SIGNAL(try_to_attack(int,int)), this, SLOT(stop_to_eat(int,int)));
    connect(this, SIGNAL(be_debuffed()), this, SLOT(slow_down()));
    if(parent->cars[loc] != nullptr){   //生成时若该行还有小推车，将该僵尸与小推车关联
        connect(parent->cars[loc], SIGNAL(kill(int)), this, SLOT(die_now(int)));//小推车杀死僵尸
        connect(this, SIGNAL(activate_car()), parent->cars[loc], SLOT(activate()));//僵尸激活小推车
    }
    movie()->start();
    show();
    ani->start();

}

void Zombie::change_to_formal_state(){              //该函数使僵尸进入下一阶段
    if(state_now < state_number){
        if(if_stop)                                 //此时僵尸正在吃东西，设置下一阶段吃东西的动画
            setMovie(eat_movs[state_now]);
        else                                        //此时僵尸在前进，设置下一阶段前进动画
            setMovie(movs[state_now]);
        movie()->start();
    }
    if(state_now == state_number){                  //僵尸已到死亡状态
        if(!if_stop)
            ani->stop();
        eating->stop();
        debuff->stop();
        once_movie* die_mov = new once_movie(":/images/zdie.gif");          //设置倒下的动画
        once_movie* head_mov = new once_movie(":/images/zhead.gif");
        setMovie(die_mov);
        connect(die_mov, SIGNAL(finished()), die_mov, SLOT(deleteLater()));
        connect(die_mov, SIGNAL(finished()), this, SLOT(is_to_die()));
        QLabel* die_lab = new QLabel((QWidget*)parent);                     //设置头掉落的动画
        die_lab->setAttribute(Qt::WA_TransparentForMouseEvents, true);
        die_lab->setMovie(head_mov);
        die_lab->setGeometry(x() + 10, y(), width(), height());
        connect(head_mov, SIGNAL(finished()), head_mov, SLOT(deleteLater()));
        connect(head_mov, SIGNAL(finished()), die_lab, SLOT(deleteLater()));
        die_lab->show();
        die_mov->start();
        head_mov->start();
    }
}

void Zombie::stop_to_eat(int a,int b){                      //僵尸遇到植物，停下来吃东西
    if_stop=1;
    ani->pause();
    setMovie(eat_movs[state_now]);
    movie()->start();
    enemy = parent->plants[b][a];
    eating->start();
}

void Zombie::move_forward(){                            //植物被吃完，僵尸继续前进
    if(state_now >= state_number)
        return;
    if_stop = 0;
    setMovie(movs[state_now]);
    movie()->start();
    enemy = nullptr;
    eating->stop();
    ani->start();
}

void Zombie::attack_enemy(){                        //僵尸进食状态下周期性执行，对面前的植物造成伤害
    enemy->hurt();
}


void Zombie::slow_down(){                           //僵尸被寒冰射手子弹打中，进入减速状态

    debuff->start();
    if(if_debuffed)
        return;
    if_debuffed = 1;
    if(!if_stop)
        ani->stop();
    ani->setStartValue(geometry());
    ani->setEndValue(QRect(0, y(), width(), height()));
    ani->setDuration(200* (x() - 0)/speed);
    eating->setInterval(eating->interval() * 2);
    if(!if_stop)
        ani->start();
}

void Zombie::recover_from_debuff(){             //减速状态持续时间已到，解除减速

    if_debuffed = 0;
    if(!if_stop)
        ani->stop();
    ani->setStartValue(geometry());
    ani->setEndValue(QRect(10, y(), width(), height()));
    ani->setDuration(100* (x() - 0)/speed);
    eating->setInterval(eating->interval() / 2);
    if(!if_stop)
        ani->start();
}


void Zombie::die_now(int X){                    //僵尸被小推车杀死，立即进入死亡状态
    if(abs(X - x() - 50) < 20 && strength > 0){
        mutex->lock();
        strength = 0;
        state_now = state_number;
        emit change_state();
    }
}


void Zombie::run(){                                                 //主要操作函数

    if(floor(fmin(full_strength - strength, full_strength) * state_number / full_strength) > state_now){//根据血量更新状态
        //mutex->lock();
        state_now = floor(fmin(full_strength - strength, full_strength) * state_number / full_strength);
        emit change_state();
    }
    if(state_now >= state_number)
        return;

    if(x() < 10)                                                    //触发小推车
        emit activate_car();

    int ypos = (y() -40)/100;                                       //遍历该行子弹，受到攻击
    parent->bul_mutex[ypos]->lock();
    for(int i = 0;i<parent->bullets[ypos].count();i++)
        if(!(parent->bullets[ypos][i]->is_dead) && abs(parent->bullets[ypos][i]->x() - x() - 50)<20){
            if(x() < 1000)
                strength -= parent->bullets[ypos][i]->attack;
            if(parent->bullets[ypos][i]->is_debuff)
                emit be_debuffed();
            parent->bullets[ypos][i]->is_dead = 1;
        }
    parent->bul_mutex[ypos]->unlock();

    if(if_debuffed)                                          //减速状态下，动画本身也放慢速度，更加真实
         movie()->setSpeed(50);
    else
         movie()->setSpeed(100);

    int xpos = (x() + 30)/100;                                  //判断当前位置有无植物，进行攻击
    if(xpos >= 0 && xpos < 9 && ypos >= 0 && ypos < 5 && parent->plants[ypos][xpos] != nullptr && !if_stop)
        emit try_to_attack(xpos, ypos);
    if(xpos >= 0 && xpos < 9 && ypos >= 0 && ypos < 5 && parent->plants[ypos][xpos] == nullptr && if_stop)
        emit move();
}


void Zombie::deleteLater(){                             //延时析构
    ani->deleteLater();
    eating->deleteLater();
    debuff->deleteLater();
    for(int i = 0;i<state_number; i++)
        movs[i]->deleteLater();
    for(int i = 0;i<state_number; i++)
        eat_movs[i]->deleteLater();
    QLabel::deleteLater();
}


ordinary::ordinary(int loc, GameWidget* parent):Zombie(loc, 10, 1, 2, 1, 2, ordinary_formal, ordinary_eat, parent){
        //普通僵尸构造
}


barricade::barricade(int loc, GameWidget* parent):Zombie(loc, 20, 1, 2, 1, 3, barricade_formal, barricade_eat, parent){
        //路障僵尸构造
}

drums::drums(int loc, GameWidget* parent):Zombie(loc, 30, 1, 2, 1, 3, drums_formal, drums_eat, parent){
        //铁通僵尸构造
}
