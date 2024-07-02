#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "plant/plant.h"
#include <QLabel>
#include <QMovie>
#include <QMutex>
#include <QPropertyAnimation>
#include <QThread>
#include <QTimer>

class GameWidget;
class Zombie;

class once_movie : public QMovie
{
    Q_OBJECT
  public:
    once_movie(QString s);
    ~once_movie() noexcept;

  signals:
    void once_finished();

  public slots:
    void check_if_finished(int frameNumber);
};

class Zombie : public QLabel
{
    Q_OBJECT

  public:
    double strength, attack, full_strength; // 满血血量，攻击力，当前血量
    double speed;                           // 速度
    int state_number, state_now;            // 阶段总数，当前阶段数
    bool if_stop = 0, if_debuffed = 0, if_dead = 0; // 是否正在吃东西，是否被减速，是否已经死亡

    once_movie **movs, **eat_movs; // 各阶段行走动画与进食动画
    QPropertyAnimation *ani;
    QTimer *debuff;         // debuff时间倒计时
    QTimer *eating;         // 周期性对植物造成伤害
    Plant *enemy = nullptr; // 面前的植物
    GameWidget *parent;     // 父对象
    QMutex *mutex;

    Zombie(int loc, double fs, double a, double sp, float es, int st, QString *movie_names,
           QString *eat_movie_names, GameWidget *ptr);
    ~Zombie() noexcept;
    virtual void run();

  public slots:
    virtual void change_to_formal_state();
    void stop_to_eat(int a, int b);
    void move_forward();
    void slow_down();
    void recover_from_debuff();
    void attack_enemy();
    void deleteLater();
    void die_now(int X);
    void is_to_die() { if_dead = 1; }

  signals:
    void shut_down();
    void move();
    void change_state();
    void debuffed();
    void try_to_attack(int a, int b);
    void activate_car();
    void be_debuffed();
};

class ordinary : public Zombie
{
    Q_OBJECT
  public:
    ordinary(int loc, GameWidget *parent = nullptr);

  private slots:
};

class barricade : public Zombie
{
    Q_OBJECT
  public:
    barricade(int loc, GameWidget *parent = nullptr);
};

class drums : public Zombie
{
    Q_OBJECT
  public:
    drums(int loc, GameWidget *parent = nullptr);
};

#endif // ZOMBIE_H
